// Copyright 2020 Sony Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <cstdio>
#include <memory>
#include <utility>

#include "rcutils/cmdline_parser.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"
#include "test_stability_msgs/msg/data.hpp"
#include "test_stability_msgs/msg/result.hpp"


using namespace std::chrono_literals;

const char* program_name = "sender";

void usage() {
  std::cout << program_name << " usage:\n"
    << "      [-s message_size]: message size of test data, default value is '4KB'\n"
    << "                         (supports unit for 'KB', 'MB' and 'GB')\n"
    << "      [-t topic_name]: topic name of test data, default value is 'DefaultTopic'\n"
    << "      [-w wait_subscriber_count]: wait subscriber to continue, default value is '1'\n"
    << "      [-l loop_count]: publish test data count, default value is '1000'\n"
    << "      [-f frequency]: publish test data frequency(Hz), default value is '100'\n"
    << "      [-q qos_profile]: qos_profile can be 0(reliable) or 1(best effort), default value is '0'\n"
    <<"\n"
    << "  E.g.:\n"
    << "    ros2 run test_statility_nodes " << program_name << "\n"
    << std::endl;
}

uint64_t GetMessageSize(const std::string& message_size)
{
  static std::map<std::string, uint64_t> size_map = {
    {"KB", 1024},
    {"MB", 1024*1024},
    {"GB", 1024*1024*1024},
  };

  std::string number = message_size;
  std::string postfix;
  for (size_t i = 0; i < message_size.length(); ++i) {
    if (!isdigit(message_size[i])) {
      number = message_size.substr(0, i);
      postfix = message_size.substr(i);
      break;
    }
  }

  if (number.empty()) {
    return 0;
  }

  uint64_t ret = std::stoul(number);
  if (postfix.empty()) {
    return ret;
  }

  std::transform(postfix.begin(), postfix.end(), postfix.begin(), ::toupper);
  auto iter = size_map.find(postfix);
  if (iter != size_map.end()) {
    ret *= iter->second;
  } else {
    ret = 0;
  }

  return ret;
}

class Sender : public rclcpp::Node
{
public:
  RCLCPP_SMART_PTR_DEFINITIONS(Sender)

  Sender(rclcpp::NodeOptions options,
    const std::string& topic_name,
    const std::string& message_size,
    uint32_t wait_subscriber_count,
    uint64_t loop_count,
    double frequency,
    uint32_t qos_profile)
  : Node(program_name, options),
    topic_name_(topic_name),
    wait_subscriber_count_(wait_subscriber_count),
    message_size_(message_size),
    loop_count_(loop_count),
    frequency_(frequency),
    qos_profile_(qos_profile)
  {
    CheckArguments();

    data_ = (char*)malloc(buffer_size_);
    if (data_ == NULL) {
      std::stringstream err;
      err << "out of memory: allocate memory size '" << buffer_size_ << "'.";
      RCLCPP_ERROR(this->get_logger(), err.str());
      throw std::runtime_error(err.str());
    }
    memset(data_, 0xff, buffer_size_);

    auto check_publisher_subscription_count =
      [this]() -> void
      {
        if (check_count(remapping_topic_name_, 1, true) &&
          check_count(remapping_topic_name_, wait_subscriber_count_, false) &&
          check_count(remapping_topic_name_+"Finish", 1, true) &&
          check_count(remapping_topic_name_+"Finish", wait_subscriber_count_, false) &&
          check_count(remapping_topic_name_+"Result", wait_subscriber_count_, true) &&
          check_count(remapping_topic_name_+"Result", 1, false)) {
          check_timer_->cancel();
          RCLCPP_INFO(this->get_logger(),
            "Ready to send test data message for topic %s",
            remapping_topic_name_.c_str());
          timer_->reset();
        }
      };

    auto publish_data_message =
      [this]() -> void
      {
        auto msg = std::make_unique<test_stability_msgs::msg::Data>();
        msg->id = count_id_++;
        msg->data.resize(buffer_size_);
        memcpy(&msg->data[0], data_, buffer_size_);
        msg->header.stamp = this->get_clock()->now();
        RCLCPP_DEBUG(this->get_logger(),
          "Send test data message, id: %llu",
          msg->id);
        pub_data_->publish(std::move(msg));

        if (count_id_ > loop_count_)
        {
          timer_->cancel();
          RCLCPP_INFO(this->get_logger(),
            "Send %llu messages with frequency %lf",
            loop_count_, frequency_);
          // sleep seconds to make subscriber get the last test data message possible
          // before getting the finish message
          std::this_thread::sleep_for(5s);

          RCLCPP_INFO(this->get_logger(), "Send finished message");
          auto finish_msg = std::make_unique<std_msgs::msg::Bool>();
          finish_msg->data = true;
          pub_finish_->publish(std::move(finish_msg));

          // the subscriber with topic 'finish' in receiver maybe not live,
          // use a timer to output the final result even if not get all of the result data
          result_timer_->reset();
        }
      };

    auto result_callback =
      [this](const test_stability_msgs::msg::Result::SharedPtr msg) -> void
      {
        static uint32_t get_result_count = 0;
        test_result_list_.insert({msg->result_name, msg});
        if (++get_result_count == wait_subscriber_count_) {
          print_result();
        }
      };

    rclcpp::QoS data_qos = rclcpp::QoS(rclcpp::KeepLast(100));
    if (qos_profile_ == 0) {
      data_qos = data_qos.reliable();
    } else if (qos_profile_ == 1) {
      data_qos = data_qos.best_effort();
    } else {
      throw std::runtime_error("qos profile can only be 0 or 1");
    }
    pub_data_ = this->create_publisher<test_stability_msgs::msg::Data>(topic_name_, data_qos);
    remapping_topic_name_ = pub_data_->get_topic_name();

    rclcpp::QoS finish_qos = rclcpp::QoS(rclcpp::KeepAll()).reliable();
    pub_finish_ = this->create_publisher<std_msgs::msg::Bool>(
      remapping_topic_name_+"Finish", finish_qos);

    rclcpp::QoS result_qos = finish_qos;
    sub_result_ = this->create_subscription<test_stability_msgs::msg::Result>(
      remapping_topic_name_+"Result", result_qos, result_callback);

    check_timer_ = this->create_wall_timer(10s, check_publisher_subscription_count);

    std::chrono::nanoseconds ns{int64_t(1000000000/frequency_)};
    timer_ = this->create_wall_timer<int64_t, std::nano>(ns, publish_data_message);
    timer_->cancel();

    result_timer_ = this->create_wall_timer(60s,
      [this]() {
        RCLCPP_INFO(this->get_logger(), "Result timer was triggered");
        print_result();
      });
    result_timer_->cancel();
  }

  ~Sender() {
    if (data_) {
      free(data_);
    }
  }

private:

  void CheckArguments() {
    std::stringstream err;
    buffer_size_ = GetMessageSize(message_size_);
    if (buffer_size_ == 0) {
      err << "invalid argument: message size '" << message_size_ << "' argument is invalid.";
    }

    if (wait_subscriber_count_ < 1) {
      err << "invalid argument: wait subscriber count '" << wait_subscriber_count_
        << "' must be greater than 0.";
    }

    if (loop_count_ < 1) {
      err << "invalid argument: loop count '" << loop_count_ << "' must be greater than 0.";
    }

    if (frequency_ < .0f) {
      err << "invalid argument: frequency '" << frequency_ << "' must be greater than 0.";
    }

    if (!err.str().empty()) {
      throw std::runtime_error(err.str());
    }
  }

  bool check_count(const std::string& topic_name, uint32_t expected_count, bool pub)
  {
    size_t count;
    if (pub) {
      count = this->count_publishers(topic_name);
    } else {
      count = this->count_subscribers(topic_name);
    }
    if (count != expected_count) {
      RCLCPP_INFO(this->get_logger(),
        "The count of %s with topic '%s' (%zu) is less than %u. Continue to wait...",
        pub ? "publisher" : "subscriber",
        topic_name.c_str(),
        count,
        expected_count);
      return false;
    }
    return true;
  };

  void print_result()
  {
    RCLCPP_INFO(this->get_logger(),
      "Publisher:Subscriber(s)=1:%u, test result of topic %s with message_size(%s), loop_count(%llu), frequency(%lf)",
      wait_subscriber_count_,
      remapping_topic_name_.c_str(),
      message_size_.c_str(),
      loop_count_,
      frequency_);
    RCLCPP_INFO(this->get_logger(),
      "           %-30s, %12s, %12s, %12s, %12s",
      "name",
      "average(s)",
      "min(s)",
      "max(s)",
      "lost count");
    for (auto&item: test_result_list_) {
      RCLCPP_INFO(this->get_logger(),
        "get result %-30s, %12.9lf, %12.9lf, %12.9lf, %12llu",
        item.second->result_name.c_str(),
        item.second->average_sec,
        item.second->min_sec,
        item.second->max_sec,
        (item.second->lost_count == std::numeric_limits<unsigned long long>::max())
          ? loop_count_ : item.second->lost_count);
    }
    if (test_result_list_.size() != wait_subscriber_count_) {
      RCLCPP_WARN(this->get_logger(), "other results from subscriber not received.");
    }
    RCLCPP_INFO(this->get_logger(), "exit by launch_test");

    std::this_thread::sleep_for(5s);
    rclcpp::shutdown();
  }

  std::string topic_name_;
  std::string remapping_topic_name_;
  uint32_t wait_subscriber_count_;
  std::string message_size_;
  uint64_t buffer_size_;
  uint64_t loop_count_;
  double frequency_;
  uint32_t qos_profile_;
  uint64_t count_id_ = 1;
  rclcpp::Publisher<test_stability_msgs::msg::Data>::SharedPtr pub_data_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr pub_finish_;
  rclcpp::Subscription<test_stability_msgs::msg::Result>::SharedPtr sub_result_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::TimerBase::SharedPtr check_timer_;
  rclcpp::TimerBase::SharedPtr result_timer_;
  char* data_;
  std::multimap<std::string, test_stability_msgs::msg::Result::SharedPtr> test_result_list_;  // ordered map
};

int main(int argc, char * argv[]){
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);

  // parse arguments
  if (rcutils_cli_option_exist(argv, argv + argc, "-h")) {
    usage();
    return 0;
  }

  char * cli_option = nullptr;

  std::string message_size = "4KB";
  std::string topic_name = "DefaultTopic";
  uint32_t wait_subscriber_count = 1;
  uint64_t loop_count = 1000;
  double frequency = 100;
  uint32_t qos_profile = 0;

  cli_option = rcutils_cli_get_option(argv, argv + argc, "-s");
  if (nullptr != cli_option) {
    message_size = std::string(cli_option);
  }

  cli_option = rcutils_cli_get_option(argv, argv + argc, "-t");
  if (nullptr != cli_option) {
    topic_name = std::string(cli_option);
  }

  cli_option = rcutils_cli_get_option(argv, argv + argc, "-w");
  if (nullptr != cli_option) {
    wait_subscriber_count = std::stoul(cli_option);
  }

  cli_option = rcutils_cli_get_option(argv, argv + argc, "-l");
  if (nullptr != cli_option) {
    loop_count = std::stoull(cli_option);
  }

  cli_option = rcutils_cli_get_option(argv, argv + argc, "-f");
  if (nullptr != cli_option) {
    frequency = std::stod(cli_option);
  }

  cli_option = rcutils_cli_get_option(argv, argv + argc, "-q");
  if (nullptr != cli_option) {
    qos_profile = std::stoul(cli_option);
  }

  rclcpp::NodeOptions options = rclcpp::NodeOptions();

  try {
    auto node = Sender::make_shared(
      options, topic_name, message_size, wait_subscriber_count, loop_count, frequency, qos_profile);
    rclcpp::spin(node);
    rclcpp::shutdown();
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
    return 1;
  }
  return 0;
}
