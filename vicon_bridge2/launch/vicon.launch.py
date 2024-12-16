from launch import LaunchDescription
from launch_ros.actions import Node
import os

def generate_launch_description():

    hostname = os.environ['VICON_IP']
    buffer_size = 200
    topic_namespace = 'vicon'

    return LaunchDescription([Node(
            package='vicon_bridge2', executable='vicon_client', output='screen',
            parameters=[{'hostname': hostname, 'buffer_size': buffer_size, 'namespace': topic_namespace}]
        )])
