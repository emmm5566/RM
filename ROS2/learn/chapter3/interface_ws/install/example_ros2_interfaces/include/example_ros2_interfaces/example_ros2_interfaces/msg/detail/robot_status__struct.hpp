// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from example_ros2_interfaces:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef EXAMPLE_ROS2_INTERFACES__MSG__DETAIL__ROBOT_STATUS__STRUCT_HPP_
#define EXAMPLE_ROS2_INTERFACES__MSG__DETAIL__ROBOT_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__example_ros2_interfaces__msg__RobotStatus __attribute__((deprecated))
#else
# define DEPRECATED__example_ros2_interfaces__msg__RobotStatus __declspec(deprecated)
#endif

namespace example_ros2_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RobotStatus_
{
  using Type = RobotStatus_<ContainerAllocator>;

  explicit RobotStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0ul;
      this->pose = 0.0f;
    }
  }

  explicit RobotStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0ul;
      this->pose = 0.0f;
    }
  }

  // field types and members
  using _status_type =
    uint32_t;
  _status_type status;
  using _pose_type =
    float;
  _pose_type pose;

  // setters for named parameter idiom
  Type & set__status(
    const uint32_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__pose(
    const float & _arg)
  {
    this->pose = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint32_t STATUS_MOVEING =
    1u;
  static constexpr uint32_t STATUS_STOP =
    1u;

  // pointer types
  using RawPtr =
    example_ros2_interfaces::msg::RobotStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const example_ros2_interfaces::msg::RobotStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<example_ros2_interfaces::msg::RobotStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<example_ros2_interfaces::msg::RobotStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      example_ros2_interfaces::msg::RobotStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<example_ros2_interfaces::msg::RobotStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      example_ros2_interfaces::msg::RobotStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<example_ros2_interfaces::msg::RobotStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<example_ros2_interfaces::msg::RobotStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<example_ros2_interfaces::msg::RobotStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__example_ros2_interfaces__msg__RobotStatus
    std::shared_ptr<example_ros2_interfaces::msg::RobotStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__example_ros2_interfaces__msg__RobotStatus
    std::shared_ptr<example_ros2_interfaces::msg::RobotStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotStatus_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->pose != other.pose) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotStatus_

// alias to use template instance with default allocator
using RobotStatus =
  example_ros2_interfaces::msg::RobotStatus_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t RobotStatus_<ContainerAllocator>::STATUS_MOVEING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t RobotStatus_<ContainerAllocator>::STATUS_STOP;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace example_ros2_interfaces

#endif  // EXAMPLE_ROS2_INTERFACES__MSG__DETAIL__ROBOT_STATUS__STRUCT_HPP_
