from launch import LaunchDescription
from launch_ros.actions import Node
# 封装终端指令相关类--------------
from launch.actions import ExecuteProcess
# from launch.substitutions import FindExecutable
# 参数声明与获取-----------------
# from launch.actions import DeclareLaunchArgument
# from launch.substitutions import LaunchConfiguration
# 文件包含相关-------------------
# from launch.actions import IncludeLaunchDescription
# from launch.launch_description_sources import PythonLaunchDescriptionSource
# 分组相关----------------------
# from launch_ros.actions import PushRosNamespace
# from launch.actions import GroupAction
# 事件相关----------------------
from launch.event_handlers import OnProcessStart, OnProcessExit
from launch.actions import ExecuteProcess, RegisterEventHandler,LogInfo
# 获取功能包下share目录路径-------
# from ament_index_python.packages import get_package_share_directory

"""
    需求:为 turtlesim_node 节点添加事件,
    事件1:节点启动时调用spawn服务生成新乌龟;
    事件2:节点关闭时,输出日志信息。
"""

def generate_launch_description():
    # 创建turtlesim_node节点
    turtle = Node(
        package="turtlesim",
        executable="turtlesim_node"
    )

    # 封装命令
    # ros2 service call /spawn turtlesim/srv/Spawn "{'x': 8.0,'y': 3.0}"
    spawn = ExecuteProcess(
        cmd=["ros2 service call /spawn turtlesim/srv/Spawn \"{'x': 8.0,'y': 3.0}\""], #嵌套""使用\防止错误解析
        output="both",
        shell=True
    )
 
    """
        event_handler: 注册的事件对象
            event_handler: 注册的事件对象
        OnProcessStart: 是启动事件对象
            target_action: 被注册事件的目标对象
            on_start: 事件触发时的执行逻辑
    """
    # 注册事件1
    event_start = RegisterEventHandler(
        event_handler=OnProcessStart(
            target_action=turtle,
            on_start=spawn
        )
    )

    """
        OnProcessExit: 退出事件对象
            target_action: 被注册事件的目标对象
            on_exit: 事件触发时的执行逻辑
        LogInfo: 日志输出对象
            msg: 被输出的日志信息
    """
    # 注册事件2
    event_exit = RegisterEventHandler(
        event_handler=OnProcessExit(
            target_action=turtle,
            # on_exit=LogInfo(msg="turtlesim_node 退出") 也可以不放在列表里
            on_exit=[LogInfo(msg="turtlesim_node 退出")]
        )
    )

    return LaunchDescription([turtle, event_start, event_exit])