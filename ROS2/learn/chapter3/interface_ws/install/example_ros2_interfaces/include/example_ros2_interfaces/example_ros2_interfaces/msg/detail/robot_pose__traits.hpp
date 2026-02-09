// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from example_ros2_interfaces:msg/RobotPose.idl
// generated code does not contain a copyright notice

#ifndef EXAMPLE_ROS2_INTERFACES__MSG__DETAIL__ROBOT_POSE__TRAITS_HPP_
#define EXAMPLE_ROS2_INTERFACES__MSG__DETAIL__ROBOT_POSE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "example_ros2_interfaces/msg/detail/robot_pose__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace example_ros2_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const RobotPose & msg,
  std::ostream & out)
{
  out << "{";
  // member: status
  {
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << ", ";
  }

  // member: pose
  {
    out << "pose: ";
    to_flow_style_yaml(msg.pose, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RobotPose & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << "\n";
  }

  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose:\n";
    to_block_style_yaml(msg.pose, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RobotPose & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace example_ros2_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use example_ros2_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const example_ros2_interfaces::msg::RobotPose & msg,
  std::ostream & out, size_t indentation = 0)
{
  example_ros2_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use example_ros2_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const example_ros2_interfaces::msg::RobotPose & msg)
{
  return example_ros2_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<example_ros2_interfaces::msg::RobotPose>()
{
  return "example_ros2_interfaces::msg::RobotPose";
}

template<>
inline const char * name<example_ros2_interfaces::msg::RobotPose>()
{
  return "example_ros2_interfaces/msg/RobotPose";
}

template<>
struct has_fixed_size<example_ros2_interfaces::msg::RobotPose>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Pose>::value> {};

template<>
struct has_bounded_size<example_ros2_interfaces::msg::RobotPose>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Pose>::value> {};

template<>
struct is_message<example_ros2_interfaces::msg::RobotPose>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // EXAMPLE_ROS2_INTERFACES__MSG__DETAIL__ROBOT_POSE__TRAITS_HPP_
