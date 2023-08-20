# ros2_stablity_test basic design

## source code structure

```
ros2_stablity_test

	test_stability_msgs
		CMakeLists.txt
		msg/
			data.msg
			result.msg
		package.xml

	test_stability_nodes
		CHANGELOG.rst
		CMakeLists.txt
		package.xml
		src/
			sender.cpp
			receiver.cpp
	launch_test
		test_remote.py
```

## Message

### data.msg

It's for sender to publish test data to receiver.

```
	std_msgs/Header header
	uint64 id
	uint8[] data
```

### result.msg

It's for receiver to publish calculated result to sender.

```
	string result_name
	float64 average_sec
	float64 min_sec
	float64 max_sec
	uint64 lost_count
```


## Nodes

### Sender

- create publisher with data(data.msg), publisher with finish(bool.msg) and subscriber with result(result.msg)
- wait subscriber count
- if subscriber count matched, publish data
- after publish all data, publish finish
- wait result subscirber's callback, if 'get result count' == 'wait subscriber count', print result, exit

```
	init
		parse_args to get topic_name, message_size, loop_count, wait_subscriber_count
		create publisher with data (qos: best_effort)
		create publisher with finish (qos: reliable)
		create subscriber with result (qos: reliable)
		create a send_data memory
		memset(send_data, 0xff, message_size);

	run
		start a timer to check subscriber count is matched with wait_subscriber_count

	timer_callback
		subscriber_count = node.count_subscribers(topic_name)
		if subscriber_count == wait_subscriber_count
			call publish message func
			return

	publish message func
		for (int i = 0; i < loop_count; ++i)
			Message msg;
			msg.id = i
			msg.timestamp = ros.time()
			memcpy(msg.data, send_data, message_size)
			data_publisher.publish(msg)
		finish_publisher.publish
		use a new result_timer to output the final result even if sender not get all of the result data

	callback of result_subscriber message func
		result++
		result_list.push_back
		if (result == wait_subscriber_count)
			print "publisher:subscriber = 1:subscriber_count  average min max remark"
			for result_list
				print each result
			ros::shutdown()
```

### Receiver

- create subscriber with data(data.msg), subscriber with finish(bool.msg) and publisher with result(result.msg)
- get data in subscriber callback, if msg.id not matched, put miss id into a list and print miss message
- after receiving finish message, calculate the result and publish result data

```
	init
		parse_args to get topic_name
		create subscriber with data (qos: best_effort)
		create subscriber with finish (qos: reliable)
		create publisher with result (qos: reliable)
		next_id = 0
		set<uint64_t> lost_id_list;     // to know which message id was lost
		vector<double> time_stamp_list;

	run
		subscriber(call_back)

	data subscriber callback
		msg = get()
		if (msg.id != next_id)
			for (int i = next_id; i < msg.id; ++i)
				lost_id_list.insert(i)
                print "miss message"
		else
			current = ros:time();
			time_stamp_list.push_back(current - msg.header.timestamp)
		next_id = msg.id + 1;

	finish subscriber callback
		calculate aver, min, max of time_stample_list
		lost_count = lost_id_list.szie()
		update result msg
		result_publisher.publish(result)
		ros::shutdown()
```


## Test

### launch testing

It need to launch remote application, so it need to use 'ssh' command to run remote command (ssh configuration need to be set in all remote machine at the beginning).

- test_stability_nodes/launch_testing/test_remote.py

```
@pytest.mark.launch_test
@launch_testing.parametrize('message_size', ['4KB', '64KB', '256KB', '2MB', '8MB'])
generate_test_description
    # to generate executeprocess list by a config.yaml(config.json) contains machine information
    ssh ${ssh_url} -C ". ${project_path}/setup.bash && ros2 run test_stability_nodes sender "+ arguments

@launch_testing.post_shutdown_test()
class TestProcessOutput(unittest.TestCase):
    // add some test here to check exit code and output
```

