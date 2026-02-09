// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interfaces:msg/MyMessage.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__MY_MESSAGE__STRUCT_H_
#define CUSTOM_INTERFACES__MSG__DETAIL__MY_MESSAGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'content'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/MyMessage in the package custom_interfaces.
/**
  * 创建接口功能包
  * ros2 pkg create custom_interfaces --build-type ament_cmake --dependencies rosidl_default_generators
  * rosidl_default_generators：用于自动生成消息对应的 C++/Python 代码，所有自定义接口的依赖项
  * 在功能包status_interfaces下面新建msg(话题)/srv(服务)文件夹
  * 在msg/srv文件夹下创建文件（消息接口），文件使用驼峰命名法，第一个字母大写
  * 话题的消息接口是.msg，服务的是.srv
 */
typedef struct custom_interfaces__msg__MyMessage
{
  /// 自定义消息：包含一个字符串和一个整数
  /// 字符串内容
  rosidl_runtime_c__String content;
  /// 数字
  int32_t num;
} custom_interfaces__msg__MyMessage;

// Struct for a sequence of custom_interfaces__msg__MyMessage.
typedef struct custom_interfaces__msg__MyMessage__Sequence
{
  custom_interfaces__msg__MyMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__msg__MyMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__MY_MESSAGE__STRUCT_H_
