"""Launch a Phidgets temperature in a component container."""

import launch
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode


def generate_launch_description():
    """Generate launch description with multiple components."""
    container = ComposableNodeContainer(
        name='robp_phidget_container',
        namespace='',
        package='rclcpp_components',
        executable='component_container',
        composable_node_descriptions=[
                ComposableNode(
                    package='robp_phidgets_temperature',
                    plugin='robp::phidgets::Temperature',
                    name='robp_phidgets_temperature'),
        ],
        output='both',
    )

    return launch.LaunchDescription([container])
