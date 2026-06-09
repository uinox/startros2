
ros2 pkg create demo_python_topic --build-type ament_python --dependencies rclpy example_interfaces --license Apache-2.0

cd novels
python3 -m http.server

colcon build --packages-select demo_python_topic

### 查看topic列表，-v表示详细信息
ros2 topic list -v

sudo apt install python3-pip -y
sudo apt install espeak-ng -y
pip3 install espeakng

espeakng报错：找不到包，使用subprocess替代

### 创建功能包：
ros2 pkg create demo_cpp_topic --build-type ament_cmake --dependencies rclcpp geometry_msgs turtlesim --license Apache-2.0


### 打开海龟模拟器
ros2 run turtlesim turtlesim_node

### 查看turtlesim节点信息
ros2 node info /turtlesim

### 输出海龟当前的位姿
ros2 topic echo /turtle1/pose

colcon build --packages-select demo_cpp_topic
ros2 run demo_cpp_topic turtle_circle

### 查看turtlesim_msgs/msg/Pose 接口定义，老版本使用turtlesim/msg/Pose
ros2 interface show turtlesim_msgs/msg/Pose

### 3-25 创建接口功能包
ros2 pkg create status_interfaces --build-type ament_cmake --dependencies rosidl_default_generators builtin_interfaces --license Apache-2.0

### ros2内置的基础类型
bool
byte
char
float32, float64
int8, uint8
int16, uint16
int32, uint32
int64, uint64
string

### 
colcon build --packages-select status_interfaces

source install/setup.bash

ros2 interface show status_interfaces/msg/SystemStatus

### 创建status_publisher功能包
ros2 pkg create status_publisher --build-type ament_python --dependencies rclpy status_interface --license Apache-2.0

colcon build --packages-select status_publisher

source install/setup.bash 
ros2 interface show status_interfaces/msg/SystemStatus
ros2 run status_publisher sys_status_pub

### 功能包使用qt
ros2 pkg create status_display --build-type ament_cmake --dependencies rclcpp status_interfaces --license Apache-2.0

### status_display添加qt5依赖

    find_package(Qt5 COMPONENTS Widgets REQUIRED)

    add_executable(hello_qt src/hello_qt.cpp)

    target_link_libraries(hello_qt
    rclcpp::rclcpp
    status_interfaces::status_interfaces
    Qt5::Widgets
    )

    install(TARGETS hello_qt
    DESTINATION lib/${PROJECT_NAME}
    )

colcon build --packages-select status_display
ros2 run status_display hello_qt

### 构建status_display
添加依赖

    add_executable(sys_status_display src/sys_status_display.cpp)

    target_link_libraries(sys_status_display
        rclcpp::rclcpp
        status_interfaces::status_interfaces
        Qt5::Widgets
    )

    install(TARGETS 
        hello_qt
        sys_status_display
        DESTINATION lib/${PROJECT_NAME}
    )


colcon build --packages-select status_display
ros2 run status_display sys_status_display