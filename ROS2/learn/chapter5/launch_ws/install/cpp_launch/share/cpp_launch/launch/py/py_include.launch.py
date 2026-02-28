from launch import LaunchDescription
from launch_ros.actions import Node
# 封装终端指令相关类--------------
# from launch.actions import ExecuteProcess
# from launch.substitutions import FindExecutable
# 参数声明与获取-----------------
# from launch.actions import DeclareLaunchArgument
# from launch.substitutions import LaunchConfiguration
# 文件包含相关-------------------
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
# 分组相关----------------------
# from launch_ros.actions import PushRosNamespace
# from launch.actions import GroupAction
# 事件相关----------------------
# from launch.event_handlers import OnProcessStart, OnProcessExit
# from launch.actions import ExecuteProcess, RegisterEventHandler,LogInfo
# 获取功能包下share目录路径-------
from ament_index_python.packages import get_package_share_directory
import os

"""
    需求:在当前launch文件,包含其他launch文件
"""

def generate_launch_description():
    include = IncludeLaunchDescription(
        # launch_description_source：用于设置被包含的 launch 文件
        launch_description_source=PythonLaunchDescriptionSource(
            # launch_file_path：被包含的 launch 文件路径
            launch_file_path=os.path.join(
                get_package_share_directory("cpp_launch"),
                "launch/py",
                "py_args.launch.py" 
            )
        ),
        # launch_arguments：元组列表，每个元组中都包含参数的键和值
        launch_arguments=[{"bg_r","80"},{"bg_g","100"},{"bg_b","200"}] #根据"py_args.launch.py"设置传递参数
    )

    return LaunchDescription([include])