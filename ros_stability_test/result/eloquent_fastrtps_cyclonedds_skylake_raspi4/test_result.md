# Test result {ignore=true}

## Content {ignore=true}
<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [Test Environment](#test-environment)
- [Test statistics of wired environment](#test-statistics-of-wired-environment)
- [Test statistics of wireless environment](#test-statistics-of-wireless-environment)
- [Analysis](#analysis)
  - [error1](#error1)
  - [error2](#error2)
- [Iperf Statictics](#iperf-statictics)
  - [Test method](#test-method)
  - [Result](#result)

<!-- /code_chunk_output -->

## Test Environment

- Hardware

    - Skylake

        GenuineIntel Intel(R) Core(TM) i7-6700K CPU(x8) @ 4.00GHz, memory 31GiB

    - Raspberry Pi 4 Model B Rev 1.1

        Broadcom BCM2711, Quad core Cortex-A72 (ARM v8) 64-bit SoC @ 1.5GHz, memory 3.7GiB

- Software

    - Host
        - Ubuntu 18.04.2 Bionic on skylake
        - Ubuntu 19.10 Eoan on Raspi4
    - Docker image
        - ROS2 Eloquent


## Test statistics of wired environment

- Publisher:Subscriber(s)=1:1, test result of message_size(4KB), loop_count(100), frequency(10.000000) 
    - qos_profile(best effort )

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wired | fastrtps |Skylake-TO-Raspi4   |  0.000593871|  0.000476745|     0.001142014 |            0|
        | wired | fastrtps |Raspi4-TO-Skylake     |  0.000471831|  0.000384187|     0.000828105|            0|
        | wired | cyclonedds |Skylake-TO-Raspi4    |  0.000580745 |  0.000484319 |   0.000936323 |            0|
        | wired | cyclonedds | Raspi4-TO-Skylake  |  0.000426917|  0.000352444 |   0.000664718 |            0|
    
    - qos_profile(reliable)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wired | fastrtps |Skylake-TO-Raspi4   |  0.000580689|  0.000487777|     0.001069745 |            0|
        | wired | fastrtps |Raspi4-TO-Skylake     |  0.000544154| 0.000422945|     0.002471775|            0|
        | wired | cyclonedds |Skylake-TO-Raspi4    |  0.000539111 |  0.000443156 |   0.000907171 |            0|
        | wired | cyclonedds | Raspi4-TO-Skylake  |  0.000441283|  0.000385312 |   0.000624612 |            0|

- Publisher:Subscriber(s)=1:1, test result of message_size(64KB), loop_count(100), frequency(10.000000) 

    - qos_profile(best effort)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wired | fastrtps |Skylake-TO-Raspi4   |  0.001733301|  0.001673931 |     0.002569998 |            0|
        | wired | fastrtps |Raspi4-TO-Skylake     |  0.001683626 |  0.001433784 |     0.002545565 |            0|
        | wired | cyclonedds |Skylake-TO-Raspi4    |  0.002192074 |  0.001982511 |   0.002948377 |            0|
        | wired | cyclonedds | Raspi4-TO-Skylake  |  0.002483768 |  0.002078030 |   0.003416553 |            0|

    - qos_profile(reliable)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wired | fastrtps |Skylake-TO-Raspi4   | 0.001772677| 0.001662244|    0.002682666 |            0|
        | wired | fastrtps |Raspi4-TO-Skylake     |  0.001807633| 0.001496501|   0.002772474 |            0|
        | wired | cyclonedds |Skylake-TO-Raspi4    |  0.002101275 |  0.001918695 |   0.002631470 |            0|
        | wired | cyclonedds | Raspi4-TO-Skylake  |  0.002334532| 0.001225055 |   0.003597626 |            0|

- Publisher:Subscriber(s)=1:1, test result of message_size(256KB), loop_count(100), frequency(10.000000) 

    - qos_profile(best effort)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wired | fastrtps |Skylake-TO-Raspi4   |  0.005628272 |  0.005441823 |     0.006951751 |            0|
        | wired | fastrtps |Raspi4-TO-Skylake     |  0.005154371 |  0.004078027 |     0.008348770 |            0|
        | wired | cyclonedds |Skylake-TO-Raspi4    |  0.006960510 |  0.005015049 |   0.008490126 |            0|
        | wired | cyclonedds | Raspi4-TO-Skylake  |  0.009170841 |  0.004038855|   0.012641234|            0|

    - qos_profile(reliable)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wired | fastrtps |Skylake-TO-Raspi4   | 0.005651656|0.005535992|    0.006917605 |            0|
        | wired | fastrtps |Raspi4-TO-Skylake     |  0.004904970| 0.004170400|   0.007146957 |            0|
        | wired | cyclonedds |Skylake-TO-Raspi4    |  0.007046235 |  0.004386172 |   0.008739223 |            0|
        | wired | cyclonedds | Raspi4-TO-Skylake  |  0.008007420| 0.003590357 |  0.009262431 |            0|

- Publisher:Subscriber(s)=1:1, test result of message_size(2MB), loop_count(100), frequency(10.000000) 

    - qos_profile(best effort)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wired | fastrtps |Skylake-TO-Raspi4   |  0.041425485 |  0.040891395 |     0.046105455 |            0|
        | wired | fastrtps |Raspi4-TO-Skylake     |  0.024813258 |  0.022884209 |     0.030577164 |            0|
        | wired | cyclonedds |Skylake-TO-Raspi4    |  0.035066742 |  0.033658351 |   0.036475133 |            1|
        | wired | cyclonedds | Raspi4-TO-Skylake  |  0.033302347 |  0.030795980 |   0.036573236 |            0|

    - qos_profile(reliable)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wired | fastrtps |Skylake-TO-Raspi4   | 0.041373931|0.040771896|   0.055576524 |            0|
        | wired | fastrtps |Raspi4-TO-Skylake     |  0.025461985| 0.023353403|  0.031749353 |            0|
        | wired | cyclonedds |Skylake-TO-Raspi4    | 0.144181377 |  0.043914387 |   0.152844283 |            0|
        | wired | cyclonedds | Raspi4-TO-Skylake  | 0.035745960|0.028159029 |  0.048076018 |            0|

- Publisher:Subscriber(s)=1:1, test result of message_size(8MB), loop_count(100), frequency(10.000000) 

    - qos_profile(best effort)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wired | fastrtps |Skylake-TO-Raspi4   |  0.315898773 |  0.179967765 |     0.330380661 |            48|
        | wired | fastrtps |Raspi4-TO-Skylake     |  0.087374168 |  0.083215766 |     0.098060262 |            0|
        | wired | cyclonedds |Skylake-TO-Raspi4 ([error1](#error1)) |  0.000000000|  0.000000000|   0.000000000|          100|
        | wired | cyclonedds | Raspi4-TO-Skylake  |  0.129513552|  0.126936766|   0.131010796 |            0|

    - qos_profile(reliable)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wired | fastrtps |Skylake-TO-Raspi4   | 2.411118026|0.190464069|   6.240517037 |            0|
        | wired | fastrtps |Raspi4-TO-Skylake     | 0.147290716| 0.083946946|  0.250152016 |            0|
        | wired | cyclonedds |Skylake-TO-Raspi4    | 0.216887790 | 0.130499559 |   0.237015536 |            0|
        | wired | cyclonedds | Raspi4-TO-Skylake  | 0.112988936|0.108481244 |  0.137850262 |            0|

## Test statistics of wireless environment

While preparing environment, please refer to section ***Configure a wireless test environment [Optional]*** in [README.md](../../README.md)

- Publisher:Subscriber(s)=1:1, test result of message_size(4KB), loop_count(100), frequency(10.000000) 

    - qos_profile(best effort)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wireless | fastrtps |Skylake-TO-Raspi4   |0.014260825  |  0.006751604 |    0.098204472  | 0 |
        | wireless | fastrtps |Raspi4-TO-Skylake     | 0.010738309 | 0.004528827 |   0.137754227  | 0|
        | wireless | cyclonedds |Skylake-TO-Raspi4 | 0.011968319  | 0.005798608 | 0.053745701| 0 |
        | wireless | cyclonedds | Raspi4-TO-Skylake  | 0.006941308 | 0.004018030  | 0.084437314  | 0 |

    - qos_profile(reliable)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wireless | fastrtps |Skylake-TO-Raspi4   |0.031262344  |  0.007898629 |    0.261286131  | 0 |
        | wireless | fastrtps |Raspi4-TO-Skylake     | 0.013966974 | 0.004792813 |   0.175488181  | 0|
        | wireless | cyclonedds |Skylake-TO-Raspi4 | 0.013947243  | 0.006203035 | 0.074638368| 0 |
        | wireless | cyclonedds | Raspi4-TO-Skylake  | 0.008519552 | 0.004591073  | 0.110281629  | 0 |

- Publisher:Subscriber(s)=1:1, test result of message_size(64KB), loop_count(100), frequency(10.000000) 

    - qos_profile(best effort)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wireless | fastrtps |Skylake-TO-Raspi4   | 0.042866425 | 0.017811844 |  0.149672108    | 4 |
        | wireless | fastrtps |Raspi4-TO-Skylake   |0.022968909  |  0.015665499|   0.135741804  | 0 |
        | wireless | cyclonedds |Skylake-TO-Raspi4 |  0.071621707 |  0.017508515 |  0.382829085  |  3|
        | wireless | cyclonedds | Raspi4-TO-Skylake  |0.022264924 |  0.015060503 | 0.125686311| 0|

    - qos_profile(reliable)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wireless | fastrtps |Skylake-TO-Raspi4   |0.050050662  | 0.019790674 |  0.222176877  | 0 |
        | wireless | fastrtps |Raspi4-TO-Skylake     | 0.020082534 | 0.015435862 |   0.120350536  | 0|
        | wireless | cyclonedds |Skylake-TO-Raspi4 | 0.053234324  | 0.016925534 | 0.283985122 | 0 |
        | wireless | cyclonedds | Raspi4-TO-Skylake  | 0.022011855 | 0.015057037  | 0.046396345  | 0 |

- Publisher:Subscriber(s)=1:1, test result of message_size(256KB), loop_count(100), frequency(10.000000) 

    - qos_profile(best effort)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wireless | fastrtps |Skylake-TO-Raspi4   |0.532802540 | 0.244580836 |   0.654368560 | 87 |
        | wireless | fastrtps |Raspi4-TO-Skylake ([error1](#error1)) |0.000000000  | 0.000000000 | 0.000000000  | 100 |
        | wireless | cyclonedds |Skylake-TO-Raspi4|  0.300020555 | 0.124539597 | 0.632862710  | 76 |
        | wireless | cyclonedds | Raspi4-TO-Skylake  |0.074780722|0.050904280|  0.159862206 |  38 |
    
    - qos_profile(reliable)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wireless | fastrtps |Skylake-TO-Raspi4   |3.056263973  | 0.138599610 |  4.358994933  | 0 |
        | wireless | fastrtps |Raspi4-TO-Skylake     | 2.924486985 | 0.071144168 |   6.384970395  | 0|
        | wireless | cyclonedds |Skylake-TO-Raspi4 | 6.837790923  | 0.362395945 | 10.574221782 | 0 |
        | wireless | cyclonedds | Raspi4-TO-Skylake  | 1.025044477 | 0.078517451  | 2.108616195  | 0 |

- Publisher:Subscriber(s)=1:1, test result of message_size(2MB), loop_count(100), frequency(10.000000) 
    
    - qos_profile(best effort)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wireless | fastrtps |Skylake-TO-Raspi4 ([error1](#error1)) | 0.000000000 | 0.000000000 |  0.000000000 | 100   |
        | wireless | fastrtps |Raspi4-TO-Skylake ([error1](#error1)) | 0.000000000 | 0.000000000 |  0.000000000 | 100  |
        | wireless | cyclonedds |Skylake-TO-Raspi4 ([error1](#error1)) |   0.000000000 | 0.000000000 |  0.000000000 | 100  |
        | wireless | cyclonedds | Raspi4-TO-Skylake ([error1](#error1)) |0.000000000 | 0.000000000 |  0.000000000 | 100  |

    - qos_profile(reliable)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wireless | fastrtps |Skylake-TO-Raspi4 ([error2](#error2)) |  |  |    | |
        | wireless | fastrtps |Raspi4-TO-Skylake ([error2](#error2)) |  |  |   | |
        | wireless | cyclonedds |Skylake-TO-Raspi4 | 49.735061567  | 13.456415217 | 80.131978650 | 0 |
        | wireless | cyclonedds | Raspi4-TO-Skylake ([error2](#error2)) |  |   |   | |


- Publisher:Subscriber(s)=1:1, test result of message_size(8MB), loop_count(100), frequency(10.000000) 

    - qos_profile(best effort)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wireless | fastrtps |Skylake-TO-Raspi4 ([error1](#error1)) | 0.000000000 | 0.000000000 |  0.000000000 | 100  |
        | wireless | fastrtps |Raspi4-TO-Skylake ([error1](#error1)) |0.000000000 | 0.000000000 |  0.000000000 | 100   |
        | wireless | cyclonedds |Skylake-TO-Raspi4 ([error1](#error1)) |  0.000000000 | 0.000000000 |  0.000000000 | 100  |
        | wireless | cyclonedds | Raspi4-TO-Skylake ([error1](#error1)) |0.000000000 | 0.000000000 |  0.000000000 | 100  |

    - qos_profile(reliable)

        | type | rmw | name | average(s) | min(s) | max(s) | lost count |
        | --- | --- | --- | --- | --- | --- | --- |
        | wireless | fastrtps |Skylake-TO-Raspi4 ([error2](#error2))  |  |  |    | |
        | wireless | fastrtps |Raspi4-TO-Skylake ([error2](#error2))  |  |  |   | |
        | wireless | cyclonedds |Skylake-TO-Raspi4 | 103.914562710  |103.914562710 | 103.914562710 | 0 |
        | wireless | cyclonedds | Raspi4-TO-Skylake  |112.536306032  |   89.542440433| 124.837134044  |0|

## Analysis

### error1

Test result has been gotten. But all messages are lost.

### error2

Test result cannot be gotten.  
There are 2 cases which lead to this issue. One of below messages or both are lost. Even if set **reliable** to make sure message can be received. But while network quality is very bad, this leads liveliness check issue (That is, publisher does not detect subscriber is alive). Below message never is sent at this scenario

1. A message(finsihed) is sent from sender to receiver. Notify receiver all test data has been sent.

2. A message(result) is sent from receiver to sender. This message include test result. After receiver get above message to know all test data has been sent, receiver will prepare test result and send test result to sender.

## Iperf Statictics

### Test method

About iperf result of maximum capability, test method as follows,

- iperf server

    ```
    # iperf3 -s
    ```

- iperf client for UDP

    ```
    # iperf3 -c {REMOTE_IP} -u -b 1000M -l 65507
    NOTE: "-b 1000M" is to use maximum enough bandwidth to get an accurate result, it is better to greater than or equal to real bandwidth of NIC.
          "-l 65507" is the maximum buffer length value which is almost the same as the fragment size of DDS.
    ```

### Result

| type | direction | transfer(actual) | bandwidth | jitter | lost/total Datagrams |
| :-- | :-- | :-- | :-- | :-- | :-- |
| wired | Skylake-TO-Raspi4 | 1.10 GBytes | 941 Mbits/sec | 0.029 ms | 0/18026 (0%) |
| wired | Raspi4-TO-Skylake | 1.11 GBytes | 956 Mbits/sec | 0.072 ms | 0/18243 (0%) |
| wireless | Skylake-TO-Raspi4 | 50.2 MBytes | 42.1 Mbits/sec | 15.453 ms | 322/505 (64%) |
| wireless | Raspi4-TO-Skylake | 79.1 MBytes | 66.0 Mbits/sec | 46.974 ms | 1072/1216 (88%) |
