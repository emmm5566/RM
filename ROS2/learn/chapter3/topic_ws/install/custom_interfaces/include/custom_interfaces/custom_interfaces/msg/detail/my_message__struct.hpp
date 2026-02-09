// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from custom_interfaces:msg/MyMessage.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__MY_MESSAGE__STRUCT_HPP_
#define CUSTOM_INTERFACES__MSG__DETAIL__MY_MESSAGE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__custom_interfaces__msg__MyMessage __attribute__((deprecated))
#else
# define DEPRECATED__custom_interfaces__msg__MyMessage __declspec(deprecated)
#endif

namespace custom_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MyMessage_
{
  using Type = MyMessage_<ContainerAllocator>;

  explicit MyMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->content = "";
      this->num = 0l;
    }
  }

  explicit MyMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : content(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->content = "";
      this->num = 0l;
    }
  }

  // field types and members
  using _content_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _content_type content;
  using _num_type =
    int32_t;
  _num_type num;

  // setters for named parameter idiom
  Type & set__content(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->content = _arg;
    return *this;
  }
  Type & set__num(
    const int32_t & _arg)
  {
    this->num = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    custom_interfaces::msg::MyMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_interfaces::msg::MyMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_interfaces::msg::MyMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_interfaces::msg::MyMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::MyMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::MyMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::MyMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::MyMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_interfaces::msg::MyMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_interfaces::msg::MyMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_interfaces__msg__MyMessage
    std::shared_ptr<custom_interfaces::msg::MyMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_interfaces__msg__MyMessage
    std::shared_ptr<custom_interfaces::msg::MyMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MyMessage_ & other) const
  {
    if (this->content != other.content) {
      return false;
    }
    if (this->num != other.num) {
      return false;
    }
    return true;
  }
  bool operator!=(const MyMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MyMessage_

// alias to use template instance with default allocator
using MyMessage =
  custom_interfaces::msg::MyMessage_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__MY_MESSAGE__STRUCT_HPP_
