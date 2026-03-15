import rclpy
from rclpy.node import Node
from tf2_ros import TransformListener, Buffer #坐标监听器
from tf_transformations import euler_from_quaternion #四元数转欧拉角

class TFListener(Node):

    def __init__(self):
        super().__init__('tf2_listener')
        self.buffer = Buffer()
        self.listener = TransformListener(self.buffer, self)
        self.timer = self.create_timer(1, self.get_transform)

    def get_transform(self):
        try:
            #查询从地图坐标系到机器人底盘坐标系的变换，时间戳为0表示获取最新的变换，等待时间为1秒
            tf = self.buffer.lookup_transform( 
                'map', 'base_footprint', rclpy.time.Time(seconds=0), rclpy.time.Duration(seconds=1)) 
            transform = tf.transform
            rotation_euler = euler_from_quaternion([
                transform.rotation.x,
                transform.rotation.y,
                transform.rotation.z,
                transform.rotation.w
            ])
            self.get_logger().info(
                f'平移:{transform.translation},旋转四元数:{transform.rotation}:旋转欧拉角:{rotation_euler}')
        except Exception as e:
            self.get_logger().warn(f'不能够获取坐标变换，原因: {str(e)}')


def main():
    rclpy.init()
    node = TFListener()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
