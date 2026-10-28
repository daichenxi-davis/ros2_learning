from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='send',
            executable='publisher',
            name='my_publisher',
            output='screen' 
        ),
        Node(
            package='receive',
            executable='subscriber',
            name='my_subscriber',
            output='screen'
        )
    ])