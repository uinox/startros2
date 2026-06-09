### 
colcon build --packages-select status_interfaces

source install/setup.bash

ros2 interface show status_interfaces/msg/SystemStatus

