// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from example_ros2_interfaces:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef EXAMPLE_ROS2_INTERFACES__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_
#define EXAMPLE_ROS2_INTERFACES__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "example_ros2_interfaces/msg/detail/robot_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace example_ros2_interfaces
{

namespace msg
{

namespace builder
{

class Init_RobotStatus_pose
{
public:
  explicit Init_RobotStatus_pose(::example_ros2_interfaces::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  ::example_ros2_interfaces::msg::RobotStatus pose(::example_ros2_interfaces::msg::RobotStatus::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::example_ros2_interfaces::msg::RobotStatus msg_;
};

class Init_RobotStatus_status
{
public:
  Init_RobotStatus_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotStatus_pose status(::example_ros2_interfaces::msg::RobotStatus::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_RobotStatus_pose(msg_);
  }

private:
  ::example_ros2_interfaces::msg::RobotStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::example_ros2_interfaces::msg::RobotStatus>()
{
  return example_ros2_interfaces::msg::builder::Init_RobotStatus_status();
}

}  // namespace example_ros2_interfaces

#endif  // EXAMPLE_ROS2_INTERFACES__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_
