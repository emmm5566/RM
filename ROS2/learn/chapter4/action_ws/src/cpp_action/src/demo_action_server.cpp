/*
  需求：编写动作服务端，解析客户端提交的数字，便利该数字并累加求和，
      最终结果响应客户端，请求响应过程中生成连续反馈。
  分析：
      1.创建动作服务端对象；
      2.处理提交的目标值；
      3.生成连续反馈；
      4.响应最终结果；
      5.处理取消请求。
  流程：
      1.包含头文件；
      2.初始化ROS2客户端；
      3.自定义节点类；
        3-1.创建动作服务端对象；
        3-2.处理提交的目标值（回调函数）；
        3-3.生成连续反馈与最终响应（回调函数）；
        3-4.处理取消请求（回调函数）；
      4.调用spin函数，并传入节点对象指针；
      5.资源释放。
*/

// 1.包含头文件
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "base_interfaces_demo/action/progress.hpp"

using base_interfaces_demo::action::Progress;
using std::placeholders::_1;
using std::placeholders::_2;

// 3.自定义节点类
class ProgressActionServer : public rclcpp::Node
{
public:
  ProgressActionServer() : Node("progress_action_server_node_cpp") {
    RCLCPP_INFO(this->get_logger(), "action 服务端创建！");

    // 3-1.创建动作客户端对象；
    /*
      template<typename ActionT, typename NodeT>
      typename Server<ActionT>::SharedPtr
      create_server(
      NodeT node,
      const std::string & name,
      typename Server<ActionT>::GoalCallback handle_goal,
      typename Server<ActionT>::CancelCallback handle_cancel,
      typename Server<ActionT>::AcceptedCallback handle_accepted,
      const rcl_action_server_options_t & options = rcl_action_server_get_default_options(),
      rclcpp::CallbackGroup::SharedPtr group = nullptr)
    */
    server_ = rclcpp_action::create_server<Progress>(
      this,
      "get_sum",
      std::bind(&ProgressActionServer::handle_goal, this, _1, _2),
      std::bind(&ProgressActionServer::handle_cancel, this, _1),
      std::bind(&ProgressActionServer::handle_accepted, this, _1)
    );
  }

  /*
    std::function<GoalResponse(
      const GoalUUID &, std::shared_ptr<const typename ActionT::Goal>)>
  */
  // 3-2.处理提交的目标值（回调函数）；
  rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const Progress::Goal> goal) {
    (void)uuid; //不使用这个参数
    // 业务逻辑：判断提交的数字是否大于1,是就接收，否就拒绝
    if(goal->num <= 1) {
      RCLCPP_INFO(this->get_logger(), "提交的目标值必须大于1!");
      return rclcpp_action::GoalResponse::REJECT;
    }
    RCLCPP_INFO(this->get_logger(), "提交的目标值合法!");
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  /*
    std::function<void (std::shared_ptr<ServerGoalHandle<ActionT>>)>
  */
  // 3-3.生成连续反馈与最终响应（回调函数）；
  void execute(std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>> goal_handle) {
    // 1.生成连续反馈返回给客户端
    // void publish_feedback(std::shared_ptr<base_interfaces_demo::action::Progress_Feedback> feedback_msg)
    // 首先要获取目标值，然后遍历，遍历中进行累加，且每循环一次就计算进度，并作为连续反馈发布
    int num = goal_handle->get_goal()->num;
    int sum = 0;
    auto feedback = std::make_shared<Progress::Feedback>();
    auto result = std::make_shared<Progress::Result>();
    rclcpp::Rate rate(1.0); //设置休眠，1s/次
    for(int i = 1; i <= num; i++) {
      sum += i;
      double progress = i / (double)num; //计算进度
      feedback->progress = progress;
      goal_handle->publish_feedback(feedback);
      RCLCPP_INFO(this->get_logger(), "连续反馈中，进度:%.2f", progress);

      // 判断是否接收到了取消请求
      // 1.goal_handle->is_canceling(); 
      // bool is_canceling() const;
      // 2.goal_handle->canceled(); 
      // void canceled(std::shared_ptr<base_interfaces_demo::action::Progress_Result> result_msg)
      if(goal_handle->is_canceling()) {
        // 如果接收到了，终止程序--return
        result->sum = sum;
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "任务被取消了!");
        return;
      } 

      rate.sleep();
    }

    // 2.生成最终响应结果
    // void succeed(typename ActionT::Result::SharedPtr result_msg)
    if(rclcpp::ok()) { //如果服务端还在正常运行
      result->sum = sum;
      goal_handle->succeed(result);
      RCLCPP_INFO(this->get_logger(), "最终结果:%d", sum);
    }
  }
  void handle_accepted(std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>> goal_handle) {
    // 新建子线程处理耗时操作，避免主逻辑出现阻塞
    std::thread(std::bind(&ProgressActionServer::execute, this, goal_handle)).detach();
  }
  
  /*
    std::function<CancelResponse(std::shared_ptr<ServerGoalHandle<ActionT>>)>
  */
  // 3-4.处理取消请求（回调函数）；
  rclcpp_action::CancelResponse handle_cancel(std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>> goal_handle) {
    (void)goal_handle;
    RCLCPP_INFO(this->get_logger(), "接收到任务取消请求!");
    return rclcpp_action::CancelResponse::ACCEPT;
  }
  
private:
  rclcpp_action::Server<Progress>::SharedPtr server_;

};

int main(int argc, char** argv) 
{
  // 2.初始化ROS2客户端
  rclcpp::init(argc, argv);
  // 4.调用spin函数，并传入节点对象指针； 
  rclcpp::spin(std::make_shared<ProgressActionServer>());
  // 5.资源释放
  rclcpp::shutdown();
  return 0;
}

// -f 反馈
// ros2 action send_goal /get_sum base_interfaces_demo/action/Progress -f "{'num': 10}"