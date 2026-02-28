'''
from A import B: 直接导入 A 模块里的 B (类 / 函数 / 变量)，使用时直接写 B
import A: 导入整个 A 模块，使用时需写 A.B
'''
# 从 launch 模块导入 LaunchDescription 类
from launch import LaunchDescription
# 从 launch_ros.actions 模块导入 Node 类
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
# from ament_index_python.packages import get_package_share_directory

# def + 函数名 + 括号 + 冒号 → 函数定义
def generate_launch_description():
    '''
    类实例化：创建对象
    对象名 = 类名(参数1=值1, 参数2=值2)
    '''
    # 同时启动两个turtle节点
    # 功能包 可执行文件 节点名字
    turtle1 = Node(package="turtlesim", executable="turtlesim_node", name="t1")
    turtle2 = Node(package="turtlesim", executable="turtlesim_node", name="t2")
    
    '''
    列表：[] 有序容器
    LaunchDescription 的参数是一个列表，里面放了 turtle1、turtle2 两个对象
    ROS 2 会遍历这个列表，逐个启动里面的节点
    '''
    return LaunchDescription([turtle1, turtle2])