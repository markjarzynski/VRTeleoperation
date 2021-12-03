Place this vrteleop folder in the husky_gazebo launch directory such that the file path is: 
\opt\ros\melodic\share\husky_gazebo\launch\<all the .launch and .world files>

Then when you want to run the husky in one of the maps:
roscore
<rosbridge command>
roslaunch husky_gazebo husky_maze1.launch

