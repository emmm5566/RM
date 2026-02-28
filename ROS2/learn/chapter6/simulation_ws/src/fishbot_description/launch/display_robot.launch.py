import launch
import launch_ros
# 向robot_state_publisher提供urdf目录，通过包名字找包目录
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # 获取默认的urdf路径
    urdf_package_path = get_package_share_directory('fishbot_description') #获取share目录
    default_urdf_path = os.path.join(urdf_package_path, 'urdf', 'first_robot.urdf') #拼接出first_robot.urdf目录
    # 获取rviz配置路径
    default_rviz_config_path = os.path.join(urdf_package_path, 'config', 'rviz', 'display_robot_model.rviz') #拼接出display_robot_model.rviz目录
    # 声明一个urdf目录的参数，方便修改
    action_declare_arg_mode_path = launch.actions.DeclareLaunchArgument(
        name='model', default_value=str(default_urdf_path), description='加载的模型文件路径'
    )

    # 通过文件路径，获取内容，并转换成参数值对象，以供传入robot_state_publisher
    # substitutions替换，路径在model中，model是launch参数是对象则不能直接传需要替换
    # 1.使用 'cat空格'+路径 显示urdf文件内容
    # substitutions_command_result = launch.substitutions.Command(['cat ',
    #     launch.substitutions.LaunchConfiguration('model')])
    # 2.使用 'xacro空格'+路径 显示urdf文件内容
    substitutions_command_result = launch.substitutions.Command(['xacro ',
        launch.substitutions.LaunchConfiguration('model')])
    # 转换成参数值对象
    robot_description_value = launch_ros.parameter_descriptions.ParameterValue(
        substitutions_command_result, value_type=str)

    # 启动 robot_state_publisher 节点，并传递 urdf 文件路径作为参数
    action_robot_state_publisher = launch_ros.actions.Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        # --ros-args
        parameters=[{'robot_description':robot_description_value}] 
    )
    # ros2 run robot_state_publisher robot_state_publiser

    # 启动 joint_state_publisher 节点
    action_joint_state_publisher = launch_ros.actions.Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
    )
    # ros2 run joint_state_publisher joint_state_publisher

    # 启动 rviz2 节点
    action_rviz_node = launch_ros.actions.Node(
        package='rviz2',
        executable='rviz2',
        # ros2 run rviz2 rviz2 -d /home/emmm/Desktop/RM/ROS2/learn/chapter6/simulation_ws/src/fishbot_description/config/rviz/display_robot_model.rviz
        arguments=['-d', default_rviz_config_path] 
    )

    return launch.LaunchDescription([
        action_declare_arg_mode_path, #声明参数
        action_robot_state_publisher, #启动robot_state_publisher
        action_joint_state_publisher, #启动joint_state_publisher
        action_rviz_node #启动rviz2
    ])

# 在launch目录下
# ros2 launch display_robot.launch.py 
# ros2 launch display_robot.launch.py --debug #查看详细错误信息
# 在工作空间下
# source install/setup.zsh 
# ros2 launch fishbot_description display_robot.launch.py
# 使用xacro获取urdf内容导入model模型
# ros2 launch fishbot_description display_robot.launch.py model:=/home/emmm/Desktop/RM/ROS2/learn/chapter6/simulation_ws/src/fishbot_description/urdf/first_robot.xacro
