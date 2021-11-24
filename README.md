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

Note: ROSIntegration doesn't communicate with ros noetic, you must use ros melodic.

Follow the normal Ubuntu install of ROS Melodic at: http://wiki.ros.org/melodic/Installation/Ubuntu

Don't forge to append `source /opt/ros/melodic/setup.bash` to the end of your `.bashrc` file.

```
echo 'source /opt/ros/melodic/setup.bash' >> ~/.bashrc
```

### Compiling rosbridge

Apparently rosbridge_suite 0.11.11 broke ROSIntegration, so we'll have to use an older version: 0.11.10.

```
mkdir -p ~/ws/src
cd ~/ws/src
git clone https://github.com/RobotWebTools/rosbridge_suite -b 0.11.10
cd ~/ws
catkin_make
echo 'source $HOME/ws/devel/setup.bash' >> ~/.bashrc
```

You might also need a few more packages
```
sudo apt install ros-melodic-rosauth
sudo apt install python-pip
pip install tornado pymongo twisted
```

### Running ROS

Run the following commands in different Terminal windows

1. `roscore`
2. `roslaunch rosbridge_server rosbridge_tcp.launch bson_only_mode:=True`

#### Testing pub and subscribe

1. `rostopic pub -r 1 /example_topic std_msgs/String hello`
2. `rostopic echo /example_topic`

This should print "hello" every second in the `roslaunch echo /example_topic` window.


