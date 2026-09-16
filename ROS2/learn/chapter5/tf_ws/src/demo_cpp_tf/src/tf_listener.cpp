#include "rclcpp/rclcpp.hpp" 
#include "geometry_msgs/msg/transform_stamped.hpp" //提供消息接口
#include "tf2/LinearMath/Quaternion.h" //提供tf2::Quaternion类
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp" //消息类型转换函数
#include "tf2_ros/transform_listener.h" //坐标监听类
#include "tf2_ros/buffer.h" //提供Buffer
#include "tf2/utils.h" //提供getEulerYPR()
#include <chrono> //时间
using namespace std::chrono_literals; 

class TFListener : public rclcpp::Node 
{
private:
    //声明TF监听器指针
    std::shared_ptr<tf2_ros::TransformListener> listener_;
    //声明定时器
    rclcpp::TimerBase::SharedPtr timer_;
    //声明buffer
    std::shared_ptr<tf2_ros::Buffer> buffer_;

public:
    //构造函数
    TFListener() : Node("tf_listener") {
        //创建bufffer（传入节点时钟）
        this->buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
        //创建TF监听器
        this->listener_ = std::make_shared<tf2_ros::TransformListener>(*buffer_, this);
        //创建定时器，定时查询TF变换
        timer_ = this->create_wall_timer(6s, std::bind(&TFListener::getTransform, this));
    }
    
    void getTransform() {
        //到buffer_里查询坐标关系
        try 
        {
            //查询坐标关系(目标坐标系, 源坐标系, 当前时刻, 超时时间)
            const auto tranform = buffer_->lookupTransform(
                "base_link", "target_point", this->get_clock()->now(),
                rclcpp::Duration::from_seconds(1.0f)); //注意定时器调用时间最好大于阻塞时间
            //获取查询结果
            auto translation = tranform.transform.translation; //注意是tranform(无s).transform(有s)
            auto rotation = tranform.transform.rotation;
            //四元数转欧拉角
            double y, p, r; 
            tf2::getEulerYPR(rotation, y, p, r); //四元数对象, yaw, pitch, raw
            RCLCPP_INFO(this->get_logger(), "平移 x:%f y:%f z:%f", translation.x, translation.y, translation.z);
            RCLCPP_INFO(this->get_logger(), "旋转 yaw:%f pitch:%f row:%f", y, p, r);
        } 
        catch(const std::exception& e) //抛出异常
        { 
            RCLCPP_WARN(get_logger(), "%s", e.what());
        }
    }
};

int main(int argc, char** argv) 
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TFListener>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}






// // 同步查询（阻塞，直到获取变换或超时）
// geometry_msgs::msg::TransformStamped lookupTransform(
//   const std::string &target_frame,  // 目标坐标系（要转换到的坐标系）
//   const std::string &source_frame,  // 源坐标系（待转换的坐标系）
//   const rclcpp::Time &time,         // 查询的时间戳（rclcpp::Time(0)表示最新）
//   const rclcpp::Duration &timeout   // 超时时间（避免无限阻塞）
// ) const;