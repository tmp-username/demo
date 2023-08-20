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
#include <numeric>
#include <algorithm>
#include <functional>

#include "rcutils/cmdline_parser.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"
#include "test_stability_msgs/msg/data.hpp"
#include "test_stability_msgs/msg/result.hpp"


using namespace std::chrono_literals;

const char* program_name = "receiver";

void usage() {
  std::cout << program_name << " usage:\n"
    << "      [-t topic_name]: test data of topic name, default value is 'DefaultTopic'\n"
    << "      [-r result_name]: result name, default value is 'local-sender-receiver'\n"
    << "                        each receiver must use unique result name\n"
    << "      [-q qos_profile]: qos_profile can be 0(reliable) or 1(best effort), default value is '0'\n"
    <<"\n"
    << "  E.g.:\n"
    << "    ros2 run test_statility_nodes " << program_name << "\n"
    << std::endl;
}

class Receiver : public rclcpp::Node
{
public:
  RCLCPP_SMART_PTR_DEFINITIONS(Receiver)

  Receiver(rclcpp::NodeOptions options,
    const std::string& topic_name,
    const std::string& result_name,
    uint32_t qos_profile)
  : Node(program_name, options),
    topic_name_(topic_name),
    result_name_(result_name),
    qos_profile_(qos_profile)
  {
    auto data_callback =
      [this](const test_stability_msgs::msg::Data::SharedPtr msg) -> void
      {
        RCLCPP_DEBUG(this->get_logger(),
          "Receive test data message, id: %llu",
          msg->id);
        if (msg->id < expect_id_) {
          RCLCPP_WARN(this->get_logger(), "Received message that arrives later.");
          return;
        }
        double transmit_duration = TransmitDuration(msg->header.stamp);
        transmit_durations_.push_back(transmit_duration);

        if (msg->id != expect_id_) {
          for (uint64_t id = expect_id_; id < msg->id; ++id) {
            lost_id_list_.push_back(id);
          }
        }

        expect_id_ = msg->id + 1;
      };

    auto finish_callback =
      [this](const std_msgs::msg::Bool::SharedPtr msg) -> void
      {
        RCLCPP_INFO(this->get_logger(), "Receive finish message");
        if (msg->data) {
          auto result_msg = std::make_unique<test_stability_msgs::msg::Result>();
          result_msg->result_name = result_name_;

          if (transmit_durations_.size() > 0) {
            auto result = std::minmax_element(
              transmit_durations_.begin(), transmit_durations_.end());
            auto sum = std::accumulate(
              transmit_durations_.begin(), transmit_durations_.end(), 0.0);
            result_msg->average_sec = sum/transmit_durations_.size();
            result_msg->min_sec = *result.first;
            result_msg->max_sec = *result.second;
            result_msg->lost_count = lost_id_list_.size();
          } else {
            result_msg->lost_count = std::numeric_limits<unsigned long long>::max();
          }

          RCLCPP_INFO(this->get_logger(), "Send result message");
          pub_result_->publish(std::move(result_msg));
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
    sub_data_ = this->create_subscription<test_stability_msgs::msg::Data>(
      topic_name_, data_qos, data_callback);
    remapping_topic_name_ = sub_data_->get_topic_name();

    rclcpp::QoS finish_qos = rclcpp::QoS(rclcpp::KeepAll()).reliable();
    sub_finish_ = this->create_subscription<std_msgs::msg::Bool>(
      remapping_topic_name_+"Finish", finish_qos, finish_callback);

    rclcpp::QoS result_qos = finish_qos;
    pub_result_ = this->create_publisher<test_stability_msgs::msg::Result>(
      remapping_topic_name_+"Result", result_qos);
  }

  ~Receiver() {
    if (!lost_id_list_.empty()) {
      RCLCPP_DEBUG(this->get_logger(), "lost message id list as follows:");
      for (auto& id: lost_id_list_) {
        RCLCPP_DEBUG(this->get_logger(), "%llu ", id);
      }
    }
  }

private:
  double TransmitDuration(const builtin_interfaces::msg::Time& time) {
    return (this->get_clock()->now()-time).nanoseconds()/1000000000.0;
  }

  std::string topic_name_;
  std::string remapping_topic_name_;
  std::string result_name_;
  uint32_t qos_profile_;
  rclcpp::Subscription<test_stability_msgs::msg::Data>::SharedPtr sub_data_;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr sub_finish_;
  rclcpp::Publisher<test_stability_msgs::msg::Result>::SharedPtr pub_result_;
  std::vector<double> transmit_durations_;
  std::vector<uint64_t> lost_id_list_;
  uint64_t expect_id_ = 1;
};

int main(int argc, char * argv[]){
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);

  // parse arguments
  rclcpp::init(argc, argv);

  // parse arguments
  if (rcutils_cli_option_exist(argv, argv + argc, "-h")) {
    usage();
    return 0;
  }

  char * cli_option = nullptr;
  std::string topic_name("DefaultTopic");
  std::string result_name("local-publisher-subscriber");
  uint32_t qos_profile = 0;

  cli_option = rcutils_cli_get_option(argv, argv + argc, "-t");
  if (nullptr != cli_option) {
    topic_name = std::string(cli_option);
  }

  cli_option = rcutils_cli_get_option(argv, argv + argc, "-r");
  if (nullptr != cli_option) {
    result_name = std::string(cli_option);
  }

  cli_option = rcutils_cli_get_option(argv, argv + argc, "-q");
  if (nullptr != cli_option) {
    qos_profile = std::stoul(cli_option);
  }

  rclcpp::NodeOptions options = rclcpp::NodeOptions();

  try {
    auto node = Receiver::make_shared(options, topic_name, result_name, qos_profile);
    rclcpp::spin(node);
    rclcpp::shutdown();
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
    return 1;
  }

  return 0;
}
