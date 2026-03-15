import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/emmm/Desktop/RM/ROS2/learn/chapter7/navigation_ws/install/autopartol_robot'
