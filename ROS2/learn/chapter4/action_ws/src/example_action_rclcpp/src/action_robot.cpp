#include "example_action_rclcpp/robot.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp" //处理Action的核心库
#include "robot_control_interfaces/action/move_robot.hpp"

// 创建一个ActionServer类
class ActionRobot : public rclcpp::Node {
 public:
  //定义类型(类型别名)
  using MoveRobot = robot_control_interfaces::action::MoveRobot;
  using GoalHandleMoveRobot = rclcpp_action::ServerGoalHandle<MoveRobot>;

  //构造函数，接收节点名称
  explicit ActionRobot(const std::string& name) : Node(name) {
    RCLCPP_INFO(this->get_logger(), "节点已启动：%s.", name.c_str());

    /* 提供 目标传递服务、取消执行服务 */
    using namespace std::placeholders; //占位符命名空间
    //创建action服务端
    this->action_server_ = rclcpp_action::create_server<MoveRobot>(
      this, "move_robot",
      std::bind(&ActionRobot::handle_goal, this, _1, _2),
      std::bind(&ActionRobot::handle_cancel, this, _1),
      std::bind(&ActionRobot::handle_accepted, this, _1));
  }

 private:
  //创建Robot对象
  Robot robot; 
  //声明action服务端
  rclcpp_action::Server<MoveRobot>::SharedPtr action_server_; 

  /* 提供 目标传递服务、取消执行服务 */

  //处理收到目标的回调函数
  rclcpp_action::GoalResponse handle_goal(
   const rclcpp_action::GoalUUID& uuid, //UUID(Universally Unique Identifier通用唯一标识符),uuid是当前请求的Goal的唯一标识
   std::shared_ptr<const MoveRobot::Goal> goal) {
    RCLCPP_INFO(this->get_logger(), "收到目标请求距离:%f", goal->distance);
    (void)uuid; //屏蔽编译器警告的空操作
    //拒绝目标请求
    if(fabs(goal->distance) > 100) {
      RCLCPP_INFO(this->get_logger(), "目标距离太远，拒绝请求");
      return rclcpp_action::GoalResponse::REJECT;
    }
    //接受目标请求
    RCLCPP_INFO(this->get_logger(), "目标距离%f合理，接受请求", goal->distance);
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  //处理收到停止的回调函数
  rclcpp_action::CancelResponse handle_cancel(
   const std::shared_ptr<GoalHandleMoveRobot> goal_handle) {
    RCLCPP_INFO(this->get_logger(), "收到取消目标请求");
    (void)goal_handle; //空操作
    robot.stop_move(); //认可取消执行，让机器人停下来
    return rclcpp_action::CancelResponse::ACCEPT;
  }

  //处理确认接受执行的回调函数
  void handle_accepted(const std::shared_ptr<GoalHandleMoveRobot> goal_handle) {
    using std::placeholders::_1;
    //在一个新线程中执行移动任务
    std::thread{std::bind(&ActionRobot::execute_move, this, _1), goal_handle}.detach(); //线程分离
  } 

  //执行机器人移动
  void execute_move(const std::shared_ptr<GoalHandleMoveRobot> goal_handle) {
    //获取目标
    const auto goal = goal_handle->get_goal();
    RCLCPP_INFO(this->get_logger(), "开始执行移动%f...", goal->distance);

    auto result = std::make_shared<MoveRobot::Result>();
    rclcpp::Rate rate = rclcpp::Rate(2); //rclcpp::Rate是频率控制器，让循环代码按固定频率执行，Rate(2)希望循环每秒执行2次
    robot.set_goal(goal->distance);
    //执行移动，直到目标完成或者任务被取消
    while(rclcpp::ok() && !robot.close_goal()) {
      //移动
      robot.move_step(); 
      auto feedback = std::make_shared<MoveRobot::Feedback>();
      /* 发布 反馈话题 */
      //发布反馈
      feedback->pose = robot.get_current_pose();
      feedback->status = robot.get_status();
      goal_handle->publish_feedback(feedback);
      /* 接收 取消执行服务 */
      //检测任务是否被取消
      if(goal_handle->is_canceling()) {
        result->pose = robot.get_current_pose();
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "目标被取消");
        return;
      }
      RCLCPP_INFO(this->get_logger(), "发布反馈");
      rate.sleep(); //休眠至达到设定频率，确保整个循环的执行频率稳定在设定值
    }

    /* 提供 结果果传递服务 */
    //完成任务，发布成功结果
    result->pose = robot.get_current_pose();
    goal_handle->succeed(result);
    RCLCPP_INFO(this->get_logger(), "目标已完成，任务成功");
  }
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto action_server = std::make_shared<ActionRobot>("action_robot");
  rclcpp::spin(action_server);
  rclcpp::shutdown();
  return 0;
}



// Action 目标、反馈、结果： 客户端发送目标，服务端接收并反馈任务的执行情况，最终返回结果。
// 1*Action = 3*service + 2*topic
// 目标传递服务	-> handle_goal()	-> async_send_goal() + goal_response_callback()	-> 目标请求与响应
// 结果传递服务	-> goal_handle-succeed()/canceled()	-> result_callback()	-> 最终结果传递
// 取消执行服务	-> handle_cancel()	-> goal_handle->is_canceling()	-> 任务取消
// 反馈话题	-> goal_handle->publish_feedback()	-> feedback_callback()	-> 进度反馈
// 状态话题	-> rclcpp_action自动管理	-> rclcpp_action自动管理	-> 任务状态跟踪

//rclcpp_action是ROS2中用于处理Action的C++核心库
//主要提供两类核心接口：
//   Action 服务端：接收并处理 Goal，发送 Feedback，返回 Result；
//   Action 客户端：发送 Goal，接收 Feedback/Result，支持取消任务。

//空操作：(void)变量名
//显式告诉编译器：“我知道这个参数被声明了但暂时没使用，无需抛出「未使用参数（unused parameter）」的警告”





// 创建action服务端
// create_server()
// template<typename ActionT , typename NodeT >
// Server<ActionT>::SharedPtr rclcpp_action::create_server 	
// ( 	NodeT  	node,
// 		const std::string &  	name,
// 		typename Server< ActionT >::GoalCallback  	handle_goal,
// 		typename Server< ActionT >::CancelCallback  	handle_cancel,
// 		typename Server< ActionT >::AcceptedCallback  	handle_accepted,
// 		const rcl_action_server_options_t &  	options = rcl_action_server_get_default_options(),
// 		rclcpp::CallbackGroup::SharedPtr  	group = nullptr 
// 	) 	
// 三个回调函数，分别用于处理收到目标、收到停止、确认接受执行：
//   handle_goal，收到目标，反馈是否可以执行该目标，可以则返回ACCEPT_AND_EXECUTE,不可以则返回REJECT
//   handle_cancel，收到取消运行请求，可以则返回ACCEPT，不可以返回REJECT。
//   handle_accepted，处理接受请求，当handle_goal中对移动请求ACCEPT后则进入到这里进行执行，这里我们是单独开了个线程进行执行execute_move函数，目的是避免阻塞主线程
