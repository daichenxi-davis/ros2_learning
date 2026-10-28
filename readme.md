```
# 1. Build the workspace
colcon build --symlink-install

# 2. Source the environment
source install/setup.bash

# 3. Launch all nodes
ros2 launch bringup start.launch.py
```
