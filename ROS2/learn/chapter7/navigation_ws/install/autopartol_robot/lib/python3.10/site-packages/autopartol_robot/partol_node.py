import rclpy
from geometry_msgs.msg import PoseStamped, Pose #位姿消息类型
from nav2_simple_commander.robot_navigator import BasicNavigator, TaskResult #导航器类
from rclpy.node import Node
import time #时间模块
from tf2_ros import TransformListener, Buffer #坐标监听器
from tf_transformations import euler_from_quaternion, quaternion_from_euler #四元数转欧拉角,欧拉角转四元数
import math #角度转弧度
from sensor_msgs.msg import Image #消息接口 图像话题
from cv_bridge import CvBridge #图像格式转换
import cv2 #保存图像

class PartolNode(BasicNavigator): #BasicNavigator是Node的子类,包含导航功能
    def __init__(self, node_name='partol_node'):
        super().__init__(node_name)
        # 相关参数
        # 导航相关定义
        self.declare_parameter('initial_point', [0.0, 0.0, 0.0]) #初始点
        self.declare_parameter('target_points', [0.0, 0.0, 0.0, 1.0, 1.0, 1.57]) #目标点,三个数一个点[x1, y1, theta1, x2, y2, theta2,...],1.57为90度
        self.initial_point_ = self.get_parameter('initial_point').value #获取初始点参数
        self.target_points_ = self.get_parameter('target_points').value #获取目标点参数
        # 实时位置获取 TF 相关定义
        self.buffer_ = Buffer() #坐标变换缓冲区
        self.listener = TransformListener(self.buffer_, self) #坐标监听器
        # 订阅与保存图像相关定义
        self.declare_parameter('img_save_path', '/home/emmm/Desktop/RM/ROS2/learn/chapter7/navigation_ws/image') #图像保存路径,空表示保存到当前的相对目录
        self.img_save_path_ = self.get_parameter('img_save_path').value #获取图像保存路径参数
        self.cv_bridge_ = CvBridge()
        self.latest_img_ = None #最新图像
        self.img_sub_ = self.create_subscription(
            Image, '/camera_sensor/image_raw', self.img_callback, 1) #图像订阅者

    # 定义函数
    def img_callback(self, msg):
        """
        图像订阅回调函数,将最新的消息放到latest_image中
        """
        self.latest_img_ = msg

    def record_img(self):
        """
        保存图像
        """
        if self.latest_img_ is not None:
            pose = self.get_current_pose()
            cv_image = self.cv_bridge_.imgmsg_to_cv2(self.latest_img_) #把ros图像转换为opencv格式
            cv2.imwrite( #保存图像
                f'{self.img_save_path_}img_{pose.translation.x:3.2f}_{pose.translation.y:3.2f}.png', #保存文件的路径和名字
                cv_image)

    def get_pose_by_xyyaw(self, x, y, yaw):
        """
        return PoseStamped对象
        根据x,y坐标和yaw角度获取Pose消息
        """
        pose = PoseStamped()
        pose.header.frame_id = 'map'
        pose.pose.position.x = x
        pose.pose.position.y = y
        # 返回顺序是 xyzw
        quat = quaternion_from_euler(0, 0, yaw)
        pose.pose.orientation.x = quat[0] 
        pose.pose.orientation.y = quat[1] 
        pose.pose.orientation.z = quat[2] 
        pose.pose.orientation.w = quat[3]
        return pose 

    def init_robot_pose(self):
        """
        初始化机器人的位姿
        """
        self.initial_point_ = self.get_parameter('initial_point').value
        init_pose = self.get_pose_by_xyyaw(
            self.initial_point_[0], self.initial_point_[1], self.initial_point_[2]) 
        self.setInitialPose(init_pose) 
        self.waitUntilNav2Active() #等待导航器激活

    def get_target_points(self):
        """
        通过参数值获取目标点的集合
        """
        points = []
        self.target_points_ = self.get_parameter('target_points').value
        for index in range(int(len(self.target_points_)/3)): #每三个数一个点
            x = self.target_points_[index*3]
            y = self.target_points_[index*3+1]
            yaw = self.target_points_[index*3+2]
            points.append([x, y, yaw])
            self.get_logger().info(f"获取到目标点{index}->{x},{y},{yaw}")
        return points
    
    def nav_to_pose(self, target_point):
        """
        导航到目标点
        """
        self.goToPose(target_point)
        while not self.isTaskComplete():
            feedback = self.getFeedback()
            self.get_logger().info(f'剩余距离:{feedback.distance_remaining}')
        result = self.getResult()
        self.get_logger().info(f'导航结果:{result}')

    def get_current_pose(self):
        """
        获取机器人当前的位姿
        """
        while rclpy.ok():
            try:
                result = self.buffer_.lookup_transform('map', 'base_footprint', 
                    rclpy.time.Time(seconds=0.0), rclpy.time.Duration(seconds=1.0))
                transform = result.transform
                self.get_logger().info(f'平移:{transform.translation}')
                return transform
            except Exception as e:
                self.get_logger().warn(f'无法获取坐标变换,原因: {str(e)}')

def main():
    rclpy.init()
    
    partol = PartolNode() #节点
    # rclpy.spin(partol) #获取参数时用
    partol.init_robot_pose() #初始化机器人位姿

    while rclpy.ok():
        points = partol.get_target_points() #获取目标点集合
        for point in points:
            x, y, yaw = point[0], point[1], point[2]
            target_pose = partol.get_pose_by_xyyaw(x, y, yaw) #转换成目标点
            partol.nav_to_pose(target_pose) #导航到目标点
            partol.record_img() #记录图像

    rclpy.shutdown()



# 启动机器人节点
# ros2 run autopartol_robot partol_node --ros-args --params-file install/autopartol_robot/share/autopartol_robot/config/partol_config.yaml