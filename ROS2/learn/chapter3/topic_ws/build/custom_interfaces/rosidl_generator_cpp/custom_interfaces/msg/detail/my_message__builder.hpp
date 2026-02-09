// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_interfaces:msg/MyMessage.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__MY_MESSAGE__BUILDER_HPP_
#define CUSTOM_INTERFACES__MSG__DETAIL__MY_MESSAGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "custom_interfaces/msg/detail/my_message__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace custom_interfaces
{

namespace msg
{

namespace builder
{

class Init_MyMessage_num
{
public:
  explicit Init_MyMessage_num(::custom_interfaces::msg::MyMessage & msg)
  : msg_(msg)
  {}
  ::custom_interfaces::msg::MyMessage num(::custom_interfaces::msg::MyMessage::_num_type arg)
  {
    msg_.num = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interfaces::msg::MyMessage msg_;
};

class Init_MyMessage_content
{
public:
  Init_MyMessage_content()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MyMessage_num content(::custom_interfaces::msg::MyMessage::_content_type arg)
  {
    msg_.content = std::move(arg);
    return Init_MyMessage_num(msg_);
  }

private:
  ::custom_interfaces::msg::MyMessage msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces::msg::MyMessage>()
{
  return custom_interfaces::msg::builder::Init_MyMessage_content();
}

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__MY_MESSAGE__BUILDER_HPP_
