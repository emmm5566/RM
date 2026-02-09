// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from example_ros2_interfaces:srv/MoveRobot.idl
// generated code does not contain a copyright notice

#ifndef EXAMPLE_ROS2_INTERFACES__SRV__DETAIL__MOVE_ROBOT__STRUCT_HPP_
#define EXAMPLE_ROS2_INTERFACES__SRV__DETAIL__MOVE_ROBOT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__example_ros2_interfaces__srv__MoveRobot_Request __attribute__((deprecated))
#else
# define DEPRECATED__example_ros2_interfaces__srv__MoveRobot_Request __declspec(deprecated)
#endif

namespace example_ros2_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct MoveRobot_Request_
{
  using Type = MoveRobot_Request_<ContainerAllocator>;

  explicit MoveRobot_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->distance = 0.0f;
    }
  }

  explicit MoveRobot_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->distance = 0.0f;
    }
  }

  // field types and members
  using _distance_type =
    float;
  _distance_type distance;

  // setters for named parameter idiom
  Type & set__distance(
    const float & _arg)
  {
    this->distance = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    example_ros2_interfaces::srv::MoveRobot_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const example_ros2_interfaces::srv::MoveRobot_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<example_ros2_interfaces::srv::MoveRobot_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<example_ros2_interfaces::srv::MoveRobot_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      example_ros2_interfaces::srv::MoveRobot_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<example_ros2_interfaces::srv::MoveRobot_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      example_ros2_interfaces::srv::MoveRobot_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<example_ros2_interfaces::srv::MoveRobot_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<example_ros2_interfaces::srv::MoveRobot_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<example_ros2_interfaces::srv::MoveRobot_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__example_ros2_interfaces__srv__MoveRobot_Request
    std::shared_ptr<example_ros2_interfaces::srv::MoveRobot_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__example_ros2_interfaces__srv__MoveRobot_Request
    std::shared_ptr<example_ros2_interfaces::srv::MoveRobot_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveRobot_Request_ & other) const
  {
    if (this->distance != other.distance) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveRobot_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveRobot_Request_

// alias to use template instance with default allocator
using MoveRobot_Request =
  example_ros2_interfaces::srv::MoveRobot_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace example_ros2_interfaces


#ifndef _WIN32
# define DEPRECATED__example_ros2_interfaces__srv__MoveRobot_Response __attribute__((deprecated))
#else
# define DEPRECATED__example_ros2_interfaces__srv__MoveRobot_Response __declspec(deprecated)
#endif

namespace example_ros2_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct MoveRobot_Response_
{
  using Type = MoveRobot_Response_<ContainerAllocator>;

  explicit MoveRobot_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pose = 0.0f;
    }
  }

  explicit MoveRobot_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pose = 0.0f;
    }
  }

  // field types and members
  using _pose_type =
    float;
  _pose_type pose;

  // setters for named parameter idiom
  Type & set__pose(
    const float & _arg)
  {
    this->pose = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    example_ros2_interfaces::srv::MoveRobot_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const example_ros2_interfaces::srv::MoveRobot_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<example_ros2_interfaces::srv::MoveRobot_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<example_ros2_interfaces::srv::MoveRobot_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      example_ros2_interfaces::srv::MoveRobot_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<example_ros2_interfaces::srv::MoveRobot_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      example_ros2_interfaces::srv::MoveRobot_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<example_ros2_interfaces::srv::MoveRobot_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<example_ros2_interfaces::srv::MoveRobot_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<example_ros2_interfaces::srv::MoveRobot_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__example_ros2_interfaces__srv__MoveRobot_Response
    std::shared_ptr<example_ros2_interfaces::srv::MoveRobot_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__example_ros2_interfaces__srv__MoveRobot_Response
    std::shared_ptr<example_ros2_interfaces::srv::MoveRobot_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveRobot_Response_ & other) const
  {
    if (this->pose != other.pose) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveRobot_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveRobot_Response_

// alias to use template instance with default allocator
using MoveRobot_Response =
  example_ros2_interfaces::srv::MoveRobot_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace example_ros2_interfaces

namespace example_ros2_interfaces
{

namespace srv
{

struct MoveRobot
{
  using Request = example_ros2_interfaces::srv::MoveRobot_Request;
  using Response = example_ros2_interfaces::srv::MoveRobot_Response;
};

}  // namespace srv

}  // namespace example_ros2_interfaces

#endif  // EXAMPLE_ROS2_INTERFACES__SRV__DETAIL__MOVE_ROBOT__STRUCT_HPP_
