// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from example_ros2_interfaces:msg/RobotPose.idl
// generated code does not contain a copyright notice

#ifndef EXAMPLE_ROS2_INTERFACES__MSG__DETAIL__ROBOT_POSE__STRUCT_HPP_
#define EXAMPLE_ROS2_INTERFACES__MSG__DETAIL__ROBOT_POSE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__example_ros2_interfaces__msg__RobotPose __attribute__((deprecated))
#else
# define DEPRECATED__example_ros2_interfaces__msg__RobotPose __declspec(deprecated)
#endif

namespace example_ros2_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RobotPose_
{
  using Type = RobotPose_<ContainerAllocator>;

  explicit RobotPose_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0ul;
    }
  }

  explicit RobotPose_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0ul;
    }
  }

  // field types and members
  using _status_type =
    uint32_t;
  _status_type status;
  using _pose_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _pose_type pose;

  // setters for named parameter idiom
  Type & set__status(
    const uint32_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__pose(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->pose = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint32_t STATUS_MOVEING =
    1u;
  static constexpr uint32_t STATUS_STOP =
    2u;

  // pointer types
  using RawPtr =
    example_ros2_interfaces::msg::RobotPose_<ContainerAllocator> *;
  using ConstRawPtr =
    const example_ros2_interfaces::msg::RobotPose_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<example_ros2_interfaces::msg::RobotPose_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<example_ros2_interfaces::msg::RobotPose_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      example_ros2_interfaces::msg::RobotPose_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<example_ros2_interfaces::msg::RobotPose_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      example_ros2_interfaces::msg::RobotPose_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<example_ros2_interfaces::msg::RobotPose_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<example_ros2_interfaces::msg::RobotPose_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<example_ros2_interfaces::msg::RobotPose_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__example_ros2_interfaces__msg__RobotPose
    std::shared_ptr<example_ros2_interfaces::msg::RobotPose_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__example_ros2_interfaces__msg__RobotPose
    std::shared_ptr<example_ros2_interfaces::msg::RobotPose_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotPose_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->pose != other.pose) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotPose_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotPose_

// alias to use template instance with default allocator
using RobotPose =
  example_ros2_interfaces::msg::RobotPose_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t RobotPose_<ContainerAllocator>::STATUS_MOVEING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t RobotPose_<ContainerAllocator>::STATUS_STOP;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace example_ros2_interfaces

#endif  // EXAMPLE_ROS2_INTERFACES__MSG__DETAIL__ROBOT_POSE__STRUCT_HPP_
