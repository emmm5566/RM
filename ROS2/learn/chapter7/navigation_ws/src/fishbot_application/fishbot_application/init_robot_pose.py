#导入PoseStamped消息类型
from geometry_msgs.msg import PoseStamped 
#导入机器人导航器类，把消息类型从PoseStamped转换为geometry_msgs/msg/PoseWithCovarianceStamped消息接口
from nav2_simple_commander.robot_navigator import BasicNavigator
#导入ROS2 Python客户端库
import rclpy 

#主函数
def main():
    #初始化ROS2 Python客户端库
    rclpy.init()

    #创建机器人导航器对象(节点)
    nav = BasicNavigator()
    
    #构建初始位姿消息
    init_pose = PoseStamped() #创建一个PoseStamped消息对象(创建初始化点的对象)
    init_pose.header.frame_id = 'map' #设置坐标系为地图坐标系
    init_pose.header.stamp = nav.get_clock().now().to_msg() #设置时间戳为当前时间
    #设置初始化点的位姿信息
    init_pose.pose.position.x = 0.0 #设置x坐标
    init_pose.pose.position.y = 0.0 #设置y坐标
    init_pose.pose.orientation.w = 1.0 #设置四元数的w分量为1.0，表示没有旋转

    # 发送初始位姿给导航器
    nav.setInitialPose(init_pose) #将初始化点设置到导航器中

    #等待导航器激活
    nav.waitUntilNav2Active()

    rclpy.spin(nav) #保持节点运行，等待导航器完成任务
    rclpy.shutdown() #关闭ROS2 Python客户端库

# #程序入口
# if __name__ == '__main__':
#     main()