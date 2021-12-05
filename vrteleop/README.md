Place the `launch` and `worlds` directories in the husky_custom_gazebo directory:

```
cp -R launch $(rospack find husky_custom_gazebo)
cp -R worlds $(rospack find husy_custom_gazebo)
```

Then when you want to run the husky in one of the maps:
roscore
<rosbridge command>
roslaunch husky_custom_gazebo husky_maze1.launch

