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

### Simulating Husky

```
sudo apt install ros-melodic-husky-simulator
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

#### Simulating a Husky: Gazebo, RViz, and RQT

[Simulating Husky](http://wiki.ros.org/husky_gazebo/Tutorials/Simulating%20Husky)

Run the additional following in seperate Terminal windows

```
roslaunch husky_gazebo husky_playpen.launch
roslaunch husky_viz view_robot.launch
rqt
```

In `rqt` select Plugins->Robot Tools->Robot Steering from the top menu. Using this interface you can control the Husky.

#### AMCL

[AMCL Husky Demo](http://wiki.ros.org/husky_navigation/Tutorials/Husky%20AMCL%20Demo)

Run the additional following in a seperate Terminal window

```
roslaunch husky_navigation amcl_demo.launch
```

In RViz you should now see a map of what the robot sees.

1. Use the 2D Pose Estimate tool in the top toolbar to give amcl an initial pose estimate.
2. Use the 2D Pose Estimate tool in the top toolbar to give amcl an initial pose estimate.


#### Actual Simulated Robot position

To get the robot's actual simulated position in Gazebo instead of just the robots odometry. This command publishes that to /my_odom

```
roslaunch my_odom_publisher start_odom.launch
```

#### Realsense

Enable realsense in Husky

```
echo "export HUSKY_REALSENSE_ENABLED=1" >> ~/.bashrc
```

#### Throttle messages.

It seems like UE4 is more stable when messages are throttled.

```
rosrun topic_tools throttle messages /realsense/depth/color/points 2.0
rosrun topic_tools throttle messages /my_odom 1.0
```

