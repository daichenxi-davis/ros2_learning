import os
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    pkg_path = get_package_share_directory('bringup')
    params_file_path = os.path.join(pkg_path, 'config', 'params.yaml') 
    return LaunchDescription([
        Node(
            package='send',
            executable='publisher',
            name='my_publisher',
            output='screen' ,
            parameters=[params_file_path] 
        ),
        Node(
            package='receive',
            executable='subscriber',
            name='my_subscriber',
            output='screen'
        )
    ])