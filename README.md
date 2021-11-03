VRTeleoperation
===============

VR Teleoperation

This project requires an Unreal Engine Plugin. It's include in this project as a submodule. Please fetch it by:

```
git submodule init
git submodule update
```

ROS
---

This project requires ROS.

### Setting up VirtualBox

Skip this step if you're already running Ubuntu 20.04.

1. Do the normal Ubuntu install in VirtualBox.
2. Enable the Universe and Multiverse repos in Ubuntu: https://help.ubuntu.com/community/Repositories/Ubuntu
3. Set up a Host-Only network: https://cs4118.github.io/dev-guides/host-only-network.html

### Installing ROS in Ubuntu

Follow the normal Ubuntu install of ROS Noetic at: http://wiki.ros.org/noetic/Installation/Ubuntu

### Running ROS

Run the following commands in different Terminal windows

1. `roscore`
2. `roslaunch rosbridge_server rosbridge_tcp.launch bson_only_mode:=True`

#### Testing pub and subscribe

1. `rostopic pub -r 1 /example_topic std_msgs/String hello`
2. `rostopic echo /example_topic`

This should print "hello" every second in the `roslaunch echo /example_topic` window.


