/*  
  需求：编写静态坐标变换程序，执行时传入两个坐标系的相对位姿关系以及父子级坐标系id，
       程序运行发布静态坐标变换。
       ros2 run pkg exec x y z roll pitch yaw frame child_frame
  步骤：
    1.包含头文件；
    2.判断终端传入的参数是否合法；
    3.初始化 ROS 客户端；
    4.定义节点类；
      4-1.创建静态坐标变换发布方；
      4-2.组织并发布消息。
    5.调用 spin 函数，并传入对象指针；
    6.释放资源。
*/

// 1.包含头文件;
#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/static_transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"

// 4.自定义节点类;
class TFStaticBroadcaster: public rclcpp::Node {
  public:
    explicit TFStaticBroadcaster(char * argv[]): Node("tf_static_broadcaster_node_cpp") {
        RCLCPP_INFO(this->get_logger(), "tf_static_broadcaster_node_cpp");

        // 4-1.创建静态坐标变换发布方；
        // tf2_ros::StaticTransformBroadcaster
        broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);

        // 4-2.组织并发布消息。
        pub_static_tf(argv);
    }

  private:
    std::shared_ptr<tf2_ros::StaticTransformBroadcaster> broadcaster_;
    void pub_static_tf(char * argv[]) {
      // 组织消息
      geometry_msgs::msg::TransformStamped transform;
      transform.header.stamp = this->now(); // 获取当前时刻做时间戳
      transform.header.frame_id = argv[7]; // 父级坐标系
      transform.child_frame_id = argv[8]; // 子级坐标系
      // 设置偏移量
      transform.transform.translation.x = atof(argv[1]); // atof = ASCII to float → 把字符串转成小数（浮点数）
      transform.transform.translation.y = atof(argv[2]);
      transform.transform.translation.z = atof(argv[3]);
      // 设置四元数
      // 将欧拉角转换为四元数
      tf2::Quaternion qtn;
      qtn.setRPY(atof(argv[4]), atof(argv[5]), atof(argv[6]));
      transform.transform.rotation.x = qtn.x();
      transform.transform.rotation.y = qtn.y();
      transform.transform.rotation.z = qtn.z();
      transform.transform.rotation.w = qtn.w();
      // 发布
      broadcaster_->sendTransform(transform);
    }
};

int main(int argc, char ** argv)
{
    // 2.判断终端传入的参数是否合法；
    if(argc != 9){
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "传入的参数不合法!");
      return 1;
    }

    // 3.初始化ROS2客户端;
    rclcpp::init(argc, argv);
    // 5.调用spin函数, 并传入节点对象指针;
    auto node = std::make_shared<TFStaticBroadcaster>(argv);
    rclcpp::spin(node);
    // 6.释放资源. 
    rclcpp::shutdown();
    return 0;
}