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
from launch_ros.actions import PushRosNamespace
from launch.actions import GroupAction
# 事件相关----------------------
# from launch.event_handlers import OnProcessStart, OnProcessExit
# from launch.actions import ExecuteProcess, RegisterEventHandler,LogInfo
# 获取功能包下share目录路径-------
# from ament_index_python.packages import get_package_share_directory

"""
    需求:创建三个turtlesim_node,然后将前两个划分为一组,第三个单独一组
"""

def generate_launch_description():
    # 创建三个turtlesim_node
    turtle1 = Node(package="turtlesim", executable="turtlesim_node", name="t1")
    turtle2 = Node(package="turtlesim", executable="turtlesim_node", name="t2")
    turtle3 = Node(package="turtlesim", executable="turtlesim_node", name="t3")
    
    # 分组
    # 设置当前组命名空间，以及包含的节点
    # actions：action列表，比如被包含到组内的命名空间、节点等
    # namespace：当前组使用的命名空间
    group1 = GroupAction(actions=[PushRosNamespace("g1"),turtle1,turtle2])
    group2 = GroupAction(actions=[PushRosNamespace("g2"),turtle3])

    return LaunchDescription([group1,group2])

# ros2 node list 查看节点