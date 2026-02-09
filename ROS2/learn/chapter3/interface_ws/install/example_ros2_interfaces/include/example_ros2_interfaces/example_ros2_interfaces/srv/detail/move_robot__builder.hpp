// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from example_ros2_interfaces:srv/MoveRobot.idl
// generated code does not contain a copyright notice

#ifndef EXAMPLE_ROS2_INTERFACES__SRV__DETAIL__MOVE_ROBOT__BUILDER_HPP_
#define EXAMPLE_ROS2_INTERFACES__SRV__DETAIL__MOVE_ROBOT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "example_ros2_interfaces/srv/detail/move_robot__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace example_ros2_interfaces
{

namespace srv
{

namespace builder
{

class Init_MoveRobot_Request_distance
{
public:
  Init_MoveRobot_Request_distance()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::example_ros2_interfaces::srv::MoveRobot_Request distance(::example_ros2_interfaces::srv::MoveRobot_Request::_distance_type arg)
  {
    msg_.distance = std::move(arg);
    return std::move(msg_);
  }

private:
  ::example_ros2_interfaces::srv::MoveRobot_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::example_ros2_interfaces::srv::MoveRobot_Request>()
{
  return example_ros2_interfaces::srv::builder::Init_MoveRobot_Request_distance();
}

}  // namespace example_ros2_interfaces


namespace example_ros2_interfaces
{

namespace srv
{

namespace builder
{

class Init_MoveRobot_Response_pose
{
public:
  Init_MoveRobot_Response_pose()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::example_ros2_interfaces::srv::MoveRobot_Response pose(::example_ros2_interfaces::srv::MoveRobot_Response::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::example_ros2_interfaces::srv::MoveRobot_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::example_ros2_interfaces::srv::MoveRobot_Response>()
{
  return example_ros2_interfaces::srv::builder::Init_MoveRobot_Response_pose();
}

}  // namespace example_ros2_interfaces

#endif  // EXAMPLE_ROS2_INTERFACES__SRV__DETAIL__MOVE_ROBOT__BUILDER_HPP_
