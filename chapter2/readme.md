rm -rf build install log

conda deactivate

colcon build --packages-select demo_python_pkg

source install/setup.bash

ros2 run demo_python_pkg writer_node

conda deactivate

rm -rf build/ install/ log/

colcon build --packages-select demo_cpp_pkg

source install/setup.bash

ros2 run demo_cpp_pkg person_node
