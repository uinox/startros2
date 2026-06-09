### 启动海龟模拟器
    ros2 run turtlesim turtlesim_node
### 查询服务列表和对应接口
    ros2 service list -t
### 查看turtlesim_msgs/srv/Spawn的详细定义
    ros2 interface show turtlesim_msgs/srv/Spawn
### 通过命令行调用服务生成新的海龟
    ros2 service call /spawn turtlesim_msgs/srv/Spawn "{x: 1, y: 1}"
service call命令用于调用指定的服务，其第一个参数是服务的名字，第二个参数是服务的接口类型，第三个参数是Request数据。

### 可视化工具rqt
除了使用命令行工具调用服务，ROS2还提供了一个可视化工具rqt，终端输入rqt
    rqt

然后在窗口右边service caller下面的Service选项框里选择“/spawn”,就可以修改Request中x和y的值，然后单击Call按钮，即可完成请求。

### 查看参数相关的服务
    ros2 service list -t | grep parameter
虽然知道了参数基于服务，但使用服务的方式进行调用还是比较麻烦的，ros2有一套关于参数的工具和库可供我使用

### 查看参数列表
    ros2 param list

### 查看指定节点的参数描述
    ros2 param describe /turtlesim background_r

### 获取节点的参数值
    ros2 param get /turtlesim background_r

### 修改参数值
    ros2 param set /turtlesim background_r 255

### 导出参数到文件里
当系统有多个节点和较多参数需要配置时，逐一使用命令行配置非常麻烦，ros2提供了使用文件来配置参数的方式。首先可以将某个节点的配置到处为一个yaml格式的文件
    ros2 param dump /turtlesim > turtlesim_param.yaml

### 运行节点时指定参数文件
    ros2 run turtlesim turtlesim_node --ros-args --params-file turtlesim_param.yaml

### 查看参数使用帮助
    ros2 param --help
在rqt工具中，插件Configuration->DynamicReconfigure提供了一个可视化参数配置工具。

## 4.3 使用Python服务通信实现人脸检测
### 1. 自定义服务接口
主目录下创建chapt4_ws/src目录，src目录下创建chapt4_interfaces
    ros2 pkg create chapt4_interfaces --build-type ament_cmake --dependencies rosidl_default_generators sensor_msgs --license Apache-2.0

上面创建功能包，除了添加rosidl_default_generators作为依赖，还添加了sensor_msgs作为依赖，这是因为在sensor_msgs中定义了图像消息接口sensor_msgs/msg/Image，我们可以直接使用它作为服务接口的Request。

在src/chapt4_interfaces下面创建目录srv，srv目录下创建FaceDetector.srv

然后在CMakeLists.txt文件中进行注册

    rosidl_generate_interfaces(${PROJECT_NAME}
        "srv/FaceDetector.srv"
        DEPENDENCIES sensor_msgs
    )

功能包清单文件package.xml添加如下代码

    <member_of_group>rosidl_interface_packages</member_of_group>

声明该功能包是一个消息接口功能包

然后进行构建，运行

    colcon build --packages-select chapt4_interfaces
    source install/setup.bash
    ros2 interface show chapt4_interfaces/srv/FaceDetector

### 2. 人脸检测

这里使用face_recognition库
本地使用的conda创建的ros312env环境，因此激活该环境,安装依赖包

    pip3 install face_recognition --break-system-packages

创建功能包

    ros2 pkg create demo_python_service --build-type ament_python --dependencies rclpy chapt4_interfaces --license Apache-2.0

    colcon build --packages-select demo_python_service

    ros2 run demo_python_service learn_face_detect


### 3. 人脸检测服务实现
在src/demo_python_service/demo_python_service目录下创建face_detect_node.py

编码完成后编译运行
colcon build --packages-select demo_python_service
ros2 run demo_python_service face_detect_node
新开窗口执行
ros2 service call /face_detect chapt4_interfaces/srv/FaceDetector

### 4. 人脸客户端的实现
在src/demo_python_service/demo_python_service目录下创建
face_detect_client_node.py

resource 添加了test1.jpg

setup.py入口文件
data_files添加
    ('share/' + package_name+"/resource", ['resource/multiple.jpg', 'resource/default.jpg', 'resource/test1.jpg'])
entry_points添加
    'face_detect_client_node = demo_python_service.face_detect_client_node:main'

编译运行
    colcon build --packages-select demo_python_service
    ros2 run demo_python_service face_detect_client_node

如果报：等待服务端上线...，启动face_detect_node服务
    ros2 run demo_python_service face_detect_node

## 4.3 用C++服务通信做一个巡逻海龟

### 1. 自定义服务接口
在src/chapt4_interfaces/srv目录下创建文件Patrol.srv，编写代码清单

编译运行

    colcon build --packages-select chapt4_interfaces --allow-overriding chapt4_interfaces
    ros2 interface show chapt4_interfaces/srv/Patrol


### 2. 服务段代码实现
在chapt4_ws/src目录下，创建功能包demo_cpp_service

    ros2 pkg create demo_cpp_service --build-type ament_cmake --dependencies chapt4_interfaces rclcpp geometry_msgs turtlesim --license Apache-2.0

在src/demo_cpp_service/src下创建文件turtle_control.cpp

添加代码

编译运行

    colcon build --packages-select chapt4_interfaces --allow-overriding chapt4_interfaces

    