from geometry_msgs.msg import PoseStamped 
from nav2_simple_commander.robot_navigator import BasicNavigator
import rclpy 

def main():
    
    rclpy.init()
    
    #节点
    nav = BasicNavigator()
    #等待导航激活，检测导航是否被初始化成功，如果没有成功调用waitForInitialPose->setInitialPose发布(0,0,0)坐标点
    #如果机器人就在(0,0,0)点，导航会认为已经设置了初始位姿，导航会被激活成功
    #如果机器人不在(0,0,0)点，需要调用init_robot_pose.py手动设置初始位姿
    nav.waitUntilNav2Active() 
    goal_pose = PoseStamped()
    goal_pose.header.frame_id = 'map' 
    goal_pose.header.stamp = nav.get_clock().now().to_msg()
    goal_pose.pose.position.x = 2.0 
    goal_pose.pose.position.y = 1.0 
    goal_pose.pose.orientation.w = 1.0 
    nav.setInitialPose(goal_pose) 
    nav.goToPose(goal_pose) #发送导航目标位姿给导航(发送服务)
    while not nav.isTaskComplete(): #等待导航完成任务
        feedback = nav.getFeedback() #获取导航反馈信息
        nav.get_logger().info(f'剩余距离:{feedback.distance_remaining}') #打印剩余距离
        # nav.cancelTask() #取消导航任务(超时取消)
    result = nav.getResult() #获取导航结果
    nav.get_logger().info(f'导航结果:{result}') #打印导航结果

    # rclpy.spin(nav) 
    # rclpy.shutdown()