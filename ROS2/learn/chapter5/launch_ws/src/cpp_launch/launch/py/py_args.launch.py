from launch import LaunchDescription
from launch_ros.actions import Node
# 封装终端指令相关类--------------
# from launch.actions import ExecuteProcess
# from launch.substitutions import FindExecutable
# 参数声明与获取-----------------
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
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
    需求: 在launch文件启动时动态设置turtlesim_node的背景颜色
    实现： 
        1. 声明参数（变量）；
        2. 调用参数（变量）；
        3. 执行launch文件时动态导入参数。
"""

def generate_launch_description():

    # 1. 声明参数（变量）；
    # name：参数名称, default_value：默认值
    decl_bg_r = DeclareLaunchArgument(name="bg_r", default_value="255")
    decl_bg_g = DeclareLaunchArgument(name="bg_g", default_value="255")
    decl_bg_b = DeclareLaunchArgument(name="bg_b", default_value="255")

    # 2. 调用参数（变量）；
    turtle = Node(
        package="turtlesim",
        executable="turtlesim_node",
        parameters=[{"background_r": LaunchConfiguration("bg_r"),
                     "background_r": LaunchConfiguration("bg_g"),
                     "background_r": LaunchConfiguration("bg_b")}] #这里是参数名称
    )
    
    return LaunchDescription([decl_bg_r, decl_bg_g, decl_bg_b, turtle])

# 3. 执行launch文件时动态导入参数。
# ros2 launch cpp_launch py_args.launch.py 使用默认参数
# ros2 launch cpp_launch py_args.launch.py bg_r:=150 bg_g:=30 bg_b:=100 指定参数