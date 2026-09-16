#ifndef EXAMPLE_ACTIONI_RCLCPP_ROBOT_HPP_
#define EXAMPLE_ACTIONI_RCLCPP_ROBOT_HPP_
#include "rclcpp/rclcpp.hpp"
#include "robot_control_interfaces/action/move_robot.hpp"

//机器人类主要负责 移动机器人 和 提供当前机器人 的状态
class Robot {
 public:
  using MoveRobot = robot_control_interfaces::action::MoveRobot;  //类型别名

  Robot() = default;
  ~Robot() = default;

  float move_step();  /*移动一小步，请间隔500ms调用一次*/
  bool set_goal(float distance);  /*移动一段距离*/
  float get_current_pose();
  int get_status();
  bool close_goal();  /*是否接近目标*/
  void stop_move();  /*停止移动*/

 private:
  float current_pose_ = 0.0;  /*声明当前位置*/
  float target_pose_ = 0.0;   /*目标距离*/
  float move_distance_ = 0.0;  /*移动距离*/
  std::atomic<bool> cancel_flag_{false};  /*取消标志*/
  int status_ = MoveRobot::Feedback::STATUS_STOP;
};

#endif  // EXAMPLE_ACTIONI_RCLCPP_ROBOT_HPP_



//std::atomic:
//C++ 标准库的模板类，封装了 “原子类型”，对它的所有读写/修改操作都是原子化的
//操作要么完全执行，要么完全不执行，不会被线程调度打断
//用于多线程环境下对变量进行无锁、线程安全的操作，避免多线程同时读写变量导致的数据竞争问题

//C++ using 类型别名:
//using 别名 = 原类型(typedef 原类型 别名)