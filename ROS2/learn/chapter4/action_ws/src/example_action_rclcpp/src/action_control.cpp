#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "robot_control_interfaces/action/move_robot.hpp"

class ActionControl : public rclcpp::Node {
 public:
  //定义类型(类型别名)
  using MoveRobot = robot_control_interfaces::action::MoveRobot;
  using GoalHandleMoveRobot = rclcpp_action::ClientGoalHandle<MoveRobot>;

  //构造函数，接收节点名称和可选的节点选项
  explicit ActionControl(std::string name,
   const rclcpp::NodeOptions& node_options = rclcpp::NodeOptions())
   : Node(name, node_options) {
    RCLCPP_INFO(this->get_logger(), "节点已启动：%s.", name.c_str());

    //创建actdion客户端
    this->client_ = rclcpp_action::create_client<MoveRobot>(this, "move_robot");

    //创建定时器
    this->timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
      std::bind(&ActionControl::send_goal, this));
  }

  /* 请求 目标传递服务 */
  //定时器发送目标到动作服务器的回调函数
  void send_goal() {
    using namespace std::placeholders;

    //请求一次后就立马取消定时器，实现了节点启动后定时发一次请求的功能
    this->timer_->cancel();

    //客户端等待服务端上线超时 
    if(!this->client_->wait_for_action_server(std::chrono::seconds(10))) {
      RCLCPP_ERROR(this->get_logger(), "服务等待超时");
      rclcpp::shutdown(); //如果未能连接动作服务器，则关闭节点
      return;
    }

    //创建一个目标消息，设置目标距离为10
    auto goal_msg = MoveRobot::Goal();
    goal_msg.distance = 10; 

    //输出发送目标的信息
    RCLCPP_INFO(this->get_logger(), "发送目标");

    //设置发送目标时的回调函数
    auto send_goal_options = rclcpp_action::Client<MoveRobot>::SendGoalOptions(); 
    send_goal_options.goal_response_callback = 
      std::bind(&ActionControl::goal_response_callback, this, _1);
    send_goal_options.feedback_callback = //执行过程中进度反馈接收回调函数
      std::bind(&ActionControl::feedback_callback, this, _1, _2);
    send_goal_options.result_callback = //最终结果接收的回调函数
      std::bind(&ActionControl::result_callback, this, _1);

    //异步发送目标到动作服务器
    this->client_->async_send_goal(goal_msg, send_goal_options);
  }

  private:
   //声明action客户端
   rclcpp_action::Client<MoveRobot>::SharedPtr client_;
   //声明定时器
   rclcpp::TimerBase::SharedPtr timer_;

    /* 接收 目标传递响应 */
   //目标的响应回调函数
   void goal_response_callback(GoalHandleMoveRobot::SharedPtr goal_handle) {
    if(!goal_handle) {
      RCLCPP_ERROR(this->get_logger(), "目标被服务器拒绝");
    } else {
      RCLCPP_INFO(this->get_logger(), "目标被服务器接受，正在等待结果");
    }
   }

    /* 订阅 反馈话题 */
   //执行过程中进度反馈接收回调函数
   void feedback_callback(
    GoalHandleMoveRobot::SharedPtr, 
    const std::shared_ptr<const MoveRobot::Feedback> feedback) {
      RCLCPP_INFO(this->get_logger(), "反馈当前位置:%f", feedback->pose);
    }

    /* 接受 结果传递服务 */
   //最终结果接收的回调函数
   void result_callback(const GoalHandleMoveRobot::WrappedResult& result) {
    //根据结果的状态代码进行处理
    switch(result.code) { 
      case rclcpp_action::ResultCode::SUCCEEDED: //任务成功完成
        break;
      case rclcpp_action::ResultCode::ABORTED: //任务中止
        RCLCPP_ERROR(this->get_logger(), "目标被中止");
        return;
      case rclcpp_action::ResultCode::CANCELED: //任务被取消
        RCLCPP_ERROR(this->get_logger(), "目标被取消");
        return;
      default: //未知的结果代码
        RCLCPP_ERROR(this->get_logger(), "未知结果代码");
        return;
    }
    //输出任务执行完成后的结果信息
    RCLCPP_INFO(this->get_logger(), "接收结果:%f", result.result->pose);
    // rclcpp::shutdown(); //关闭节点
   }
};  // class ActionControl

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto action_client = std::make_shared<ActionControl>("action_control");
  rclcpp::spin(action_client);
  rclcpp::shutdown();
  return 0;
}





// 创建action客户端
// create_client() [2/2]
// template<typename ActionT , typename NodeT >
// Client<ActionT>::SharedPtr rclcpp_action::create_client 	
// ( 	NodeT  	node,
// 		const std::string &  	name,
// 		rclcpp::CallbackGroup::SharedPtr  	group = nullptr 
// 	) 	