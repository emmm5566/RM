# 启动gazebo并且加载世界模型
# 将机器人建模的xacro->urdf 转换为Gazebo的sdf，加载到gazebo中

import launch
import launch_ros
# 向robot_state_publisher提供urdf目录，通过包名字找包目录
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # 获取默认的xacro路径
    urdf_package_path = get_package_share_directory('fishbot_description') #获取功能包的share目录
    default_xacro_path = os.path.join(urdf_package_path, 'urdf', 'fishbot/fishbot.urdf.xacro') #拼接XACRO文件路径
    # 获取gazebo_world路径
    default_gazebo_world_path = os.path.join(urdf_package_path, 'world', 'custom_room.world') #拼接世界文件路径
    
    # 声明urdf目录的参数
    action_declare_arg_mode_path = launch.actions.DeclareLaunchArgument(
        name='model', default_value=str(default_xacro_path), description='加载的模型文件路径'
    )

    # 执行xacro命令，把XACRO文件转换成URDF字符串
    substitutions_command_result = launch.substitutions.Command(['xacro ',
        launch.substitutions.LaunchConfiguration('model')])
    # 封装成ROS 2参数值对象
    robot_description_value = launch_ros.parameter_descriptions.ParameterValue(
        substitutions_command_result, value_type=str)
    
    # 启动robot_state_publisher节点，发布机器人URDF到/robot_description话题
    action_robot_state_publisher = launch_ros.actions.Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description':robot_description_value}] 
    )

    # 启动 gazebo 节点，并加载世界模型
    # IncludeLaunchDescription：使用Gazebo官方的gazebo.launch.py，在launch中加载另外一个launch文件
    action_launch_gazebo = launch.actions.IncludeLaunchDescription(
        # 启动gazebo的同时加载世界模型
        # ros2 launch gazebo_ros gazebo.launch.py world:=xxx.world 
        launch.launch_description_sources.PythonLaunchDescriptionSource(
            [get_package_share_directory('gazebo_ros'), '/launch', '/gazebo.launch.py']
        ),
        # launch_arguments：传递world参数指定自定义世界，verbose=true输出详细日志
        launch_arguments=[('world', default_gazebo_world_path), ('verbose', 'true')]
    )

    # 加载机器人，把urdf转换为sdf
    # ros2 run gazebo_ros spawn_entity.py
    action_spawn_entity = launch_ros.actions.Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        # 通过话题参数加载urdf内容
        arguments=['-topic', '/robot_description', '-entity', 'fishbot']
    )

    # 加载并激活关节状态广播器
    action_load_joint_state_controller = launch.actions.ExecuteProcess(
        # .split(' ')用空格分割字符串为列表
        cmd='ros2 control load_controller fishbot_joint_state_broadcaster --set-state active'.split(' '), #注意:没有[]，因为split已经返回列表了
        # cmd=['ros2', 'control', 'load_controller', 'fishbot_joint_state_broadcaster', '--set-state', 'active'],
        output='screen'
    )

    # 加载并激活力矩控制器
    action_load_effort_controller = launch.actions.ExecuteProcess(
        cmd='ros2 control load_controller fishbot_effort_controller --set-state active'.split(' '),
        # cmd=['ros2', 'control', 'load_controller', 'fishbot_effort_controller', '--set-state', 'active'],
        output='screen'
    )

    # 加载并激活差速控制器
    action_load_diff_drive_controller = launch.actions.ExecuteProcess(
        cmd='ros2 control load_controller fishbot_diff_drive_controller --set-state active'.split(' '),
        # cmd=['ros2', 'control', 'load_controller', 'fishbot_diff_drive_controller', '--set-state', 'active'],
        output='screen'
    )

    return launch.LaunchDescription([
        action_declare_arg_mode_path, #声明参数
        action_robot_state_publisher, #启动robot_state_publisher
        action_launch_gazebo, #启动gazebo
        action_spawn_entity, #加载机器人
        launch.actions.RegisterEventHandler( #使用事件控制进程执行先后顺序
            event_handler=launch.event_handlers.OnProcessExit(
                target_action=action_spawn_entity, #加载机器人完成后
                on_exit=[
                    action_load_joint_state_controller] #加载并激活关节状态广播器
            )
        ), #加载完上一个控制器后再加载下一个控制器
        launch.actions.RegisterEventHandler( 
            event_handler=launch.event_handlers.OnProcessExit(
                target_action=action_load_joint_state_controller, #加载并激活关节状态广播器完成后
                # on_exit=[action_load_effort_controller] #加载并激活力矩控制器
                # 力矩控制器和差速控制器都控制轮子，二者不能同时调用，否则会有指令冲突
                on_exit=[action_load_diff_drive_controller] #加载并激活差速控制器
            )
        )
    ])



# ros2 launch fishbot_description gazebo_sim.launch.py
# 使用键盘控制节点移动机器人
# ros2 run teleop_twist_keyboard teleop_twist_keyboard