from launch import LaunchDescription
from launch_ros.actions import Node
# 封装终端指令相关类--------------
# from launch.actions import ExecuteProcess
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
# from launch.event_handlers import OnProcessStart, OnProcessExit
# from launch.actions import ExecuteProcess, RegisterEventHandler,LogInfo
# 获取功能包下share目录路径-------
from ament_index_python.packages import get_package_share_directory
import os # os模块 与操作系统交互，比如文件路径处理、目录操作、环境变量读取等

"""
    需求：演示 Node 的使用

    构造函数参数说明：
        :param: executable 可执行程序
        :param: package 被执行的程序所属的功能包
        :param: name 节点名称
        :param: namespace 设置命名空间
        :param: exec_name 设置程序标签
        :param: parameters 设置参数
        :param: remappings 实现话题重映射
        :param: ros_arguments 为节点传参: xx yy zz --ros-args
        :param: arguments 为节点传参: --ros-args xx yy zz
"""

def generate_launch_description():
    turtle1 = Node(
        package="turtlesim",
        executable="turtlesim_node",

        namespace="ns_1", # 设置命名空间，ns即namespace
        name="t1", # 设置节点名称
        exec_name="my_label", # 设置程序标签

        #是否自动重启
        respawn=True
    )
    turtle2 = Node(
        package="turtlesim",
        executable="turtlesim_node",
        name="t2",

        # 方式1：直接设置参数
        # parameters=[{"background_r": 255, "background_g": 0, "background_b": 0}]
        # 方式2：读取yaml文件(更常用，加载yaml文件的绝对路径)
        # ros2 param dump 导出指定节点的所有参数到 YAML 文件
        # ros2 param dump t2 --output-dir src/cpp_launch/config/
        # parameters=["/home/emmm/Desktop/RM/ROS2/learn/chapter5/launch_ws/src/cpp_launch/config/t2.yaml"]
        # 获取动态路径
        # os.path.join() 拼接文件 / 目录路径
        parameters=[os.path.join(get_package_share_directory("cpp_launch"), "config", "t2.yaml")]
    )
    turtle3 = Node(
        package="turtlesim",
        executable="turtlesim_node",
        name="t3",
        remappings=[("/turtle1/cmd_vel","cmd_vel")] #话题重映射
    )
    turtle4 = Node(
        package="turtlesim",
        executable="turtlesim_node",

        # 节点启动时传参，相当于 arguments 传参时添加前缀 --ros-args 
        # ros2 run turtlesim turtlesim_node --ros-args -remap __ns:=/t4
        ros_arguments=["--remap","__ns:=/t4_ns", "--remap","__node:=t4"]
    )
    
    return LaunchDescription([turtle1, turtle2, turtle3, turtle4])