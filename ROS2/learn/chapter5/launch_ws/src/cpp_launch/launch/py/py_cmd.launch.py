from launch import LaunchDescription
from launch_ros.actions import Node
# 封装终端指令相关类--------------
from launch.actions import ExecuteProcess
from launch.substitutions import FindExecutable
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
# from launch.event_handlers import OnProcessStart, OnProcessExit
# from launch.actions import ExecuteProcess, RegisterEventHandler,LogInfo
# 获取功能包下share目录路径-------
# from ament_index_python.packages import get_package_share_directory

"""
    需求: 启动turtlesim_node节点, 并调用指令打印乌龟的位姿信息
"""
def generate_launch_description():
    # 启动turtlesim节点
    turtle = Node(
        package="turtlesim",
        executable="turtlesim_node"
    )

    # 封装终端指令：实时打印乌龟位姿
    # cmd：要执行的终端指令列表
    # output="both"：both同时输出到日志文件和终端，默认为log日志只输出到日志文件
    # shell=True：允许执行复杂的shell指令
    cmd = ExecuteProcess(
        # cmd=["ros2 topic echo /turtle1/pose"], # 字符串形式,shell=True
        # cmd=["ros2", "topic", "echo", "/turtle1/pose"], # 拆分成列表,shell=False
        # FindExecutable(name="ros2")：自动查找系统中ros2可执行文件的绝对路径
        cmd=[FindExecutable(name="ros2"), "topic", "echo", "/turtle1/pose"],

        output="both", # 输出到终端+日志文件
        shell=False # 以shell的方式执行命令
    )
    
    return LaunchDescription([turtle, cmd])