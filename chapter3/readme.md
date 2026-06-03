
ros2 pkg create demo_python_topic --build-type ament_python --dependencies rclpy example_interfaces --license Apache-2.0

cd novels
python3 -m http.server

colcon build --packages-select demo_python_topic

查看topic列表，-v表示详细信息
ros2 topic list -v

sudo apt install python3-pip -y
sudo apt install espeak-ng -y
pip3 install espeakng

espeakng报错：找不到包，使用subprocess替代

创建功能包：
ros2 pkg create demo_cpp_topic --build-type ament_cmake --dependencies rclcpp geometry_msgs turtlesim --license Apache-2.0


打开海龟模拟器
ros2 run turtlesim turtlesim_node

查看turtlesim节点信息
ros2 node info /turtlesim

输出海龟当前的位姿
ros2 topic echo /turtle1/pose

colcon build --packages-select demo_cpp_topic
ros2 run demo_cpp_topic turtle_circle