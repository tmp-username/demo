## Test result

Based on 'wired_fastrtps_log_100msg_10hz_2001141834.log', 'wired_opensplice_log_100msg_10hz_2001141844.log',  
'wireless_fastrtps_log_100msg_10hz_2001141901.log' and 'wireless_opensplice_log_100msg_10hz_2001142058.log',
The test result as follows,

NOTE: Some minus values exist because of synchronizing the clock with NTP that using "second" as minimum unit.

- Publisher:Subscriber(s)=1:2, test result of topic /TOPIC_4KB_0 with message_size(4KB), loop_count(100), frequency(10.000000)

    | type | rmw | name | average(s) | min(s) | max(s) | lost count |
    | - | - | - | - | - | - | - |
    | wired | fastrtps |skylake-TO-rpi3-no1           |  0.010610962|  0.010489559|     0.011001107|            0|
    | wired | fastrtps |skylake-TO-rpi3-no2           |  0.007632228|  0.007481303|     0.008701494|            0|
    | wired | opensplice |skylake-TO-rpi3-no1           |  0.014328783|  0.014190177|   0.015145207|            0|
    | wired | opensplice |skylake-TO-rpi3-no2           |  0.010007875|  0.009868610|   0.010552568|            0|
    | wireless | fastrtps |skylake-TO-rpi3-no1           |  0.161662022|  0.036782152|      0.551094535|            0|
    | wireless | fastrtps |skylake-TO-rpi3-no2           |  0.173383323|  0.036544089|      0.555552951|            0|
    | wireless | opensplice |skylake-TO-rpi3-no1           | -0.036588548| -0.051342069|    0.018170155|            0|
    | wireless | opensplice |skylake-TO-rpi3-no2           | -0.002289877| -0.019491087|  0.060699418|            0|

- Publisher:Subscriber(s)=1:2, test result of topic /TOPIC_4KB_1 with message_size(4KB), loop_count(100), frequency(10.000000)

    | type | rmw | name | average(s) | min(s) | max(s) | lost count |
    | - | - | - | - | - | - | - |
    | wired | fastrtps |rpi3-no1-TO-rpi3-no2          | -0.001688833| -0.001817642|     -0.000746405|            0|
    | wired | fastrtps |rpi3-no1-TO-skylake           | -0.008989823| -0.009196395|     -0.008746009|            0|
    | wired | opensplice |rpi3-no1-TO-rpi3-no2          | -0.002123886| -0.002284682|   -0.001042455|            0|
    | wired | opensplice |rpi3-no1-TO-skylake           | -0.011221968| -0.011425908|   -0.010817841|            0|
    | wireless | fastrtps |rpi3-no1-TO-rpi3-no2          |  0.122558033|  0.003518846|      0.821207073|            0|
    | wireless | fastrtps |rpi3-no1-TO-skylake           |  0.143320612| -0.005372328|      0.887781252|            0|
    | wireless | opensplice |rpi3-no1-TO-rpi3-no2          |  0.072731043|  0.041963916|    0.374834030|            0|
    | wireless | opensplice |rpi3-no1-TO-skylake           |  0.121173639|  0.067113125|  0.485701445|            0|

- Publisher:Subscriber(s)=1:2, test result of topic /TOPIC_4KB_2 with message_size(4KB), loop_count(100), frequency(10.000000)

    | type | rmw | name | average(s) | min(s) | max(s) | lost count |
    | - | - | - | - | - | - | - |
    | wired | fastrtps |rpi3-no2-TO-rpi3-no1          |  0.004571508|  0.004389971|     0.005774564|            0|
    | wired | fastrtps |rpi3-no2-TO-skylake           | -0.005959280| -0.006134549|     -0.005638586|            0|
    | wired | opensplice |rpi3-no2-TO-rpi3-no1          |  0.006505286|  0.006318179|   0.007788132|            0|
    | wired | opensplice |rpi3-no2-TO-skylake           | -0.007048007| -0.007352071|   -0.006228794|            0|
    | wireless | fastrtps |rpi3-no2-TO-rpi3-no1          |  0.039432444|  0.009443043|      0.224477525|            0|
    | wireless | fastrtps |rpi3-no2-TO-skylake           |  0.073132310|  0.000529304|      0.536923812|            0|
    | wireless | opensplice |rpi3-no2-TO-rpi3-no1          |  0.002738368| -0.029718278|    0.394976524|            1|
    | wireless | opensplice |rpi3-no2-TO-skylake           |  0.071199485|  0.028432691|  0.503041350|            1|

- Publisher:Subscriber(s)=1:2, test result of topic /TOPIC_64KB_0 with message_size(64KB), loop_count(100), frequency(10.000000)

    | type | rmw | name | average(s) | min(s) | max(s) | lost count |
    | - | - | - | - | - | - | - |
    | wired | fastrtps |skylake-TO-rpi3-no1           |  0.015183947|  0.014711581|     0.016041750|            0|
    | wired | fastrtps |skylake-TO-rpi3-no2           |  0.010853903|  0.010610787|     0.011479036|            0|
    | wired | opensplice |skylake-TO-rpi3-no1           |  0.020260819|  0.019687575|   0.021394239|            0|
    | wired | opensplice |skylake-TO-rpi3-no2           |  0.014684167|  0.014278557|   0.015542822|            0|
    | wireless | fastrtps |skylake-TO-rpi3-no1           |  2.554950253|  0.719108898|      5.688823233|           81|
    | wireless | fastrtps |skylake-TO-rpi3-no2           |  2.871412875|  0.706093928|      5.701664326|           66|
    | wireless | opensplice |skylake-TO-rpi3-no1           |  0.701802679|  0.203076446|    2.014995404|            5|
    | wireless | opensplice |skylake-TO-rpi3-no2           |  1.080305060|  0.044426881|  2.998875399|            4|

- Publisher:Subscriber(s)=1:2, test result of topic /TOPIC_64KB_1 with message_size(64KB), loop_count(100), frequency(10.000000)

    | type | rmw | name | average(s) | min(s) | max(s) | lost count |
    | - | - | - | - | - | - | - |
    | wired | fastrtps |rpi3-no1-TO-rpi3-no2          |  0.006013425|  0.004660605|     0.007208528|            0|
    | wired | fastrtps |rpi3-no1-TO-skylake           | -0.002093729| -0.003628127|     -0.001531047|            0|
    | wired | opensplice |rpi3-no1-TO-rpi3-no2          |  0.006711681|  0.005545301|   0.008121384|            0|
    | wired | opensplice |rpi3-no1-TO-skylake           | -0.004096585| -0.005231289|   -0.003101900|            0|
    | wireless | fastrtps |rpi3-no1-TO-rpi3-no2          |  2.304007322|  0.367826250|      3.819672024|            0|
    | wireless | fastrtps |rpi3-no1-TO-skylake           |  0.796425121|  0.100911392|      1.604217217|           78|
    | wireless | opensplice |rpi3-no1-TO-rpi3-no2          |  2.521627592|  0.302433677|    4.610675572|            0|
    | wireless | opensplice |rpi3-no1-TO-skylake           |  0.634753464|  0.166337294|  1.941205132|           30|

- Publisher:Subscriber(s)=1:2, test result of topic /TOPIC_64KB_2 with message_size(64KB), loop_count(100), frequency(10.000000)

    | type | rmw | name | average(s) | min(s) | max(s) | lost count |
    | - | - | - | - | - | - | - |
    | wired | fastrtps |rpi3-no2-TO-rpi3-no1          |  0.012640738|  0.011937056|     0.014477348|            0|
    | wired | fastrtps |rpi3-no2-TO-skylake           |  0.001113948|  0.000458460|     0.002126977|            0|
    | wired | opensplice |rpi3-no2-TO-rpi3-no1          |  0.015889827|  0.014713296|   0.017824146|            0|
    | wired | opensplice |rpi3-no2-TO-skylake           |  0.000459348| -0.000563983|   0.001455053|            0|
    | wireless | fastrtps |rpi3-no2-TO-rpi3-no1          |  3.919601419|  1.020993058|      8.542466156|            1|
    | wireless | fastrtps |rpi3-no2-TO-skylake           |  2.419450499|  0.527399259|      6.082085836|           29|
    | wireless | opensplice |rpi3-no2-TO-rpi3-no1          |  2.264912303|  0.261483110|    5.377832394|            1|
    | wireless | opensplice |rpi3-no2-TO-skylake           |  0.287888800|  0.078061524|  1.906337152|           24|

- Publisher:Subscriber(s)=1:2, test result of topic /TOPIC_256KB_0 with message_size(256KB), loop_count(100), frequency(10.000000)

    | type | rmw | name | average(s) | min(s) | max(s) | lost count |
    | - | - | - | - | - | - | - |
    | wired | fastrtps |skylake-TO-rpi3-no1           |  0.024049428|  0.023783692|     0.026061649|            2|
    | wired | fastrtps |skylake-TO-rpi3-no2           |  0.019202327|  0.018879688|     0.021085181|            1|
    | wired | opensplice |skylake-TO-rpi3-no1           |  0.032660804|  0.031518944|   0.035511640|            0|
    | wired | opensplice |skylake-TO-rpi3-no2           |  0.029078519|  0.029078519|   0.029078519|            0|
    | wireless | fastrtps |skylake-TO-rpi3-no1           |  6.526167634|  3.026761000|  11.742801759|            4|
    | wireless | fastrtps |skylake-TO-rpi3-no2           |  5.982940538|  3.027789461|      9.584945390|            1|
    | wireless | opensplice |skylake-TO-rpi3-no1           |  0.000000000|  0.000000000|    0.000000000|          100|
    | wireless | opensplice |skylake-TO-rpi3-no2           |  0.000000000|  0.000000000|  0.000000000|          100|

- Publisher:Subscriber(s)=1:2, test result of topic /TOPIC_256KB_1 with message_size(256KB), loop_count(100), frequency(10.000000)

    | type | rmw | name | average(s) | min(s) | max(s) | lost count |
    | - | - | - | - | - | - | - |
    | wired | fastrtps |rpi3-no1-TO-rpi3-no2          |  0.022029630|  0.020965434|     0.023457461|            0|
    | wired | fastrtps |rpi3-no1-TO-skylake           |  0.011929844|  0.010271747|     0.013702537|            0|
    | wired | opensplice |rpi3-no1-TO-rpi3-no2          |  0.026645204|  0.024487753|   0.030867394|            0|
    | wired | opensplice |rpi3-no1-TO-skylake           |  0.013366366|  0.011199171|   0.017725719|            0|
    | wireless | fastrtps |rpi3-no1-TO-rpi3-no2          |  6.161378962|  2.266767360|  10.604599804|           51|
    | wireless | fastrtps |rpi3-no1-TO-skylake           |  6.809201136|  1.152958107|  10.758639089|           50|
    | wireless | opensplice |rpi3-no1-TO-rpi3-no2          |  1.593139201|  0.800243314|    2.386035087|            0|
    | wireless | opensplice |rpi3-no1-TO-skylake           |  0.585358496|  0.585358496|  0.585358496|            1|

- Publisher:Subscriber(s)=1:2, test result of topic /TOPIC_256KB_2 with message_size(256KB), loop_count(100), frequency(10.000000)

    | type | rmw | name | average(s) | min(s) | max(s) | lost count |
    | - | - | - | - | - | - | - |
    | wired | fastrtps |rpi3-no2-TO-rpi3-no1          |  0.028979877|  0.027250658|     0.030824794|            0|
    | wired | fastrtps |rpi3-no2-TO-skylake           |  0.015227744|  0.013352487|     0.017207357|            0|
    | wired | opensplice |rpi3-no2-TO-rpi3-no1          |  0.036223212|  0.034605739|   0.039134839|            0|
    | wired | opensplice |rpi3-no2-TO-skylake           |  0.017790940|  0.016046188|   0.019752939|            0|
    | wireless | fastrtps |rpi3-no2-TO-rpi3-no1          |  4.255857059|  1.375639484|  18.297853724|           20|
    | wireless | fastrtps |rpi3-no2-TO-skylake           |  3.889860099|  1.054808782|      9.027455917|           32|
    | wireless | opensplice |rpi3-no2-TO-rpi3-no1          |  2.867685254|  1.553713151|    4.186350955|            0|
    | wireless | opensplice |rpi3-no2-TO-skylake           |  0.584797217|  0.455832211|  0.704914319|            0|

- Publisher:Subscriber(s)=1:2, test result of topic /TOPIC_2MB_0 with message_size(2MB), loop_count(100), frequency(10.000000)

    | type | rmw | name | average(s) | min(s) | max(s) | lost count |
    | - | - | - | - | - | - | - |
    | wired | fastrtps |skylake-TO-rpi3-no1           |  0.099298178|  0.098420108|     0.104582429|            3|
    | wired | fastrtps |skylake-TO-rpi3-no2           |  0.097703883|  0.096740830|     0.103078402|            0|
    | wired | opensplice |skylake-TO-rpi3-no1           |  0.135804829|  0.127022843|   0.148654924|            3|
    | wired | opensplice |skylake-TO-rpi3-no2           |  0.138693358|  0.134834366|   0.143650630|            3|
    | wireless | fastrtps |skylake-TO-rpi3-no1           |  0.000000000|  0.000000000|      0.000000000|          100|
    | wireless | fastrtps |skylake-TO-rpi3-no2(error)    |  0.000000000|  0.000000000|      0.000000000|          100|
    | wireless | opensplice |skylake-TO-rpi3-no1(error)    |  0.000000000|  0.000000000|    0.000000000|          100|
    | wireless | opensplice |skylake-TO-rpi3-no2(error)    |  0.000000000|  0.000000000|  0.000000000|          100|

- Publisher:Subscriber(s)=1:2, test result of topic /TOPIC_2MB_1 with message_size(2MB), loop_count(100), frequency(10.000000)

    | type | rmw | name | average(s) | min(s) | max(s) | lost count |
    | - | - | - | - | - | - | - |
    | wired | fastrtps |rpi3-no1-TO-rpi3-no2          |  0.301997262|  0.164216045|     0.309076615|            0|
    | wired | fastrtps |rpi3-no1-TO-skylake           |  0.286505870|  0.144630767|     0.293487709|            0|
    | wired | opensplice |skylake-TO-rpi3-no1                  |  2.452917181|  0.211948554|    4.684102904|            0|
    | wired | opensplice |skylake-TO-rpi3-no2                  |  2.422840631|  0.167736867|    4.654747095|            0|
    | wireless | fastrtps |rpi3-no1-TO-rpi3-no2(error)   |  0.000000000|  0.000000000|      0.000000000|          100|
    | wireless | fastrtps |rpi3-no1-TO-skylake(error)    |  0.000000000|  0.000000000|      0.000000000|          100|
    | wireless | opensplice |skylake-TO-rpi3-no1(error)           |  0.000000000|  0.000000000|   0.000000000|          100|
    | wireless | opensplice |skylake-TO-rpi3-no2(error)           |  0.000000000|  0.000000000|  0.000000000|          100|

- Publisher:Subscriber(s)=1:2, test result of topic /TOPIC_2MB_2 with message_size(2MB), loop_count(100), frequency(10.000000)

    | type | rmw | name | average(s) | min(s) | max(s) | lost count |
    | - | - | - | - | - | - | - |
    | wired | fastrtps |rpi3-no2-TO-rpi3-no1          |  0.310244612|  0.173099269|     0.316539463|            0|
    | wired | fastrtps |rpi3-no2-TO-skylake           |  0.290749377|  0.150019178|     0.297780649|            0|
    | wired | opensplice |skylake-TO-rpi3-no1                  |  2.488440150|  0.221391126|    4.742986786|            0|
    | wired | opensplice |skylake-TO-rpi3-no2                  |  2.447587226|  0.171858820|    4.715923108|            0|
    | wireless | fastrtps |rpi3-no2-TO-rpi3-no1          | 38.351062934| 33.412208448|  46.106480017|           80|
    | wireless | fastrtps |rpi3-no2-TO-skylake           | 33.922625660| 26.561252313|  37.259637761|           55|
    | wireless | opensplice |skylake-TO-rpi3-no1(error)           |  0.000000000|  0.000000000|   0.000000000|          100|
    | wireless | opensplice |skylake-TO-rpi3-no2(error)           |  0.000000000|  0.000000000|  0.000000000|          100|

- Publisher:Subscriber(s)=1:2, test result of topic /TOPIC_8MB_0 with message_size(8MB), loop_count(100), frequency(10.000000)

    | type | rmw | name | average(s) | min(s) | max(s) | lost count |
    | - | - | - | - | - | - | - |
    | wired | fastrtps |skylake-TO-rpi3-no1           |  0.631805781|  0.380577927|     0.701108876|            6|
    | wired | fastrtps |skylake-TO-rpi3-no2           |  0.590115179|  0.377815643|     0.700325730|            4|
    | wired | opensplice |skylake-TO-rpi3-no1                  |  0.977077865|  0.520689324|    1.426512726|            2|
    | wired | opensplice |skylake-TO-rpi3-no2                  |  1.729629610|  0.509708477|    2.596506494|            6|
    | wireless | fastrtps |skylake-TO-rpi3-no1(error)    |  0.000000000|  0.000000000|      0.000000000|          100|
    | wireless | fastrtps |skylake-TO-rpi3-no2(error)    |  0.000000000|  0.000000000|      0.000000000|          100|
    | wireless | opensplice |skylake-TO-rpi3-no1(error)           |  0.000000000|  0.000000000|   0.000000000|          100|
    | wireless | opensplice |skylake-TO-rpi3-no2(error)           |  0.000000000|  0.000000000|  0.000000000|          100|

- Publisher:Subscriber(s)=1:2, test result of topic /TOPIC_8MB_1 with message_size(8MB), loop_count(100), frequency(10.000000)

    | type | rmw | name | average(s) | min(s) | max(s) | lost count |
    | - | - | - | - | - | - | - |
    | wired | fastrtps |rpi3-no1-TO-rpi3-no2          |  1.177416367|  0.646000294|     1.191809301|            2|
    | wired | fastrtps |rpi3-no1-TO-skylake           |  1.148861609|  0.605895076|     1.163515430|            0|
    | wired | opensplice |skylake-TO-rpi3-no1(not test)                  |  |  |  |             |
    | wired | opensplice |skylake-TO-rpi3-no2(not test)                  |  |  |  |             |
    | wireless | fastrtps |rpi3-no1-TO-rpi3-no2          |  0.000000000|  0.000000000|      0.000000000|          100|
    | wireless | fastrtps |rpi3-no1-TO-skylake(error)    |  0.000000000|  0.000000000|      0.000000000|          100|
    | wireless | opensplice |skylake-TO-rpi3-no1(not test)           |  |  |  |            |
    | wireless | opensplice |skylake-TO-rpi3-no2(not test)           |  |  |  |            |

- Publisher:Subscriber(s)=1:2, test result of topic /TOPIC_8MB_2 with message_size(8MB), loop_count(100), frequency(10.000000)

    | type | rmw | name | average(s) | min(s) | max(s) | lost count |
    | - | - | - | - | - | - | - |
    | wired | fastrtps |rpi3-no2-TO-rpi3-no1          |  1.185546125|  0.652702747|     1.209615076|            2|
    | wired | fastrtps |rpi3-no2-TO-skylake           |  1.153246413|  0.613100347|     1.167382533|            0|
    | wired | opensplice |skylake-TO-rpi3-no1(not test)                  |  |  |  |             |
    | wired | opensplice |skylake-TO-rpi3-no2(not test)                  |  |  |  |             |
    | wireless | fastrtps |rpi3-no2-TO-rpi3-no1(error)   |  0.000000000|  0.000000000|      0.000000000|          100|
    | wireless | fastrtps |rpi3-no2-TO-skylake(error)    |  0.000000000|  0.000000000|      0.000000000|          100|
    | wireless | opensplice |skylake-TO-rpi3-no1(not test)           |  |  |  |            |
    | wireless | opensplice |skylake-TO-rpi3-no2(not test)           |  |  |  |            |


## Analysis for error and not test

### error

About '(error)', the root cause is that publisher does not detect subscriber is alive (This is handled by DDS middleware. This case happen while network load is heavy which lead checking liveless packet to be discarded.), and then not to publish 'finish' or 'result' data to subscriber. sender application node use a timer to exit after publishing all test data.

### not test

About '(not test)' by using opensplice, error happened as follows.
After executing for a while, this problem will occur. Such as first time execution (for wired) in TOPIC_8MB_0 doesn't occur, but occur in TOPIC_8MB_1 (second time to execute).

```
// wired
[ERROR] [ssh-41]: process has died [pid 27009, exit code 247, cmd '/usr/bin/ssh -tt -o StrictHostKeyChecking=no -p 9922 root@192.168.66.14 source /opt/ros/eloquent/setup.bash && RCUTILS_CONSOLE_OUTPUT_FORMAT="[{severity}] [{time}] [{name}]: {message}" ROS_DOMAIN_ID=28 RMW_IMPLEMENTATION=rmw_opensplice_cpp ros2 run test_stability_nodes sender -t TOPIC_8MB_1 -s 8MB -w 2 -l 100 -f 10  --ros-args --remap __node:=sender_1_1'].

// wireless
[ERROR] [ssh-41]: process has died [pid 4568, exit code 247, cmd '/usr/bin/ssh -tt -o StrictHostKeyChecking=no -p 9922 root@192.168.66.12 source /opt/ros/eloquent/setup.bash && RCUTILS_CONSOLE_OUTPUT_FORMAT="[{severity}] [{time}] [{name}]: {message}" ROS_DOMAIN_ID=28 RMW_IMPLEMENTATION=rmw_opensplice_cpp ros2 run test_stability_nodes sender -t TOPIC_8MB_1 -s 8MB -w 2 -l 100 -f 10  --ros-args --remap __node:=sender_1_1'].
```
