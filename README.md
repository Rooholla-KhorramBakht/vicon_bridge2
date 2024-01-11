# vicon_bridge2
This repository is the combinition of the two [vicon_bridge](https://github.com/ethz-asl/vicon_bridge), and [ros2-vicon-receiver](https://github.com/OPT4SMART/ros2-vicon-receiver) projects. The ros2-vicon-receiver project uses a custom message with no timestamp and does not broadcast TF messages while vicon_bridge provides these functionalities but has no ROS2 support. To fill this gap, this repository provides a ROS2 package that similar to vicon_bridge, publishes PoseStamped and TF2 messages. 

## How to Use
Clone the repository inside your ROS2 workspace and compile:

```bash
cd your-ros2-ws/src
git clone https://github.com/Rooholla-KhorramBakht/vicon_bridge2.git
cd ..
colcon build
```
Then configure the launch file and set the `hostname` to the appropriate IP address of the Vicon server. Finally launch the node:

```bash
source install/setup.bash
ros2 launch vicon_bridge2 vicon.launch.py
```