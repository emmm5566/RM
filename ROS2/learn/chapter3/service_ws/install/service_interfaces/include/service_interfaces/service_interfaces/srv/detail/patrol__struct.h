// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from service_interfaces:srv/Patrol.idl
// generated code does not contain a copyright notice

#ifndef SERVICE_INTERFACES__SRV__DETAIL__PATROL__STRUCT_H_
#define SERVICE_INTERFACES__SRV__DETAIL__PATROL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/Patrol in the package service_interfaces.
typedef struct service_interfaces__srv__Patrol_Request
{
  /// 目标x值
  float target_x;
  /// 目标y值
  float target_y;
} service_interfaces__srv__Patrol_Request;

// Struct for a sequence of service_interfaces__srv__Patrol_Request.
typedef struct service_interfaces__srv__Patrol_Request__Sequence
{
  service_interfaces__srv__Patrol_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} service_interfaces__srv__Patrol_Request__Sequence;


// Constants defined in the message

/// Constant 'SUCCESS'.
/**
  * 定义常量，表示成功 （大写常量）
 */
enum
{
  service_interfaces__srv__Patrol_Response__SUCCESS = 1
};

/// Constant 'FAIL'.
/**
  * 定义常量，表示失败
 */
enum
{
  service_interfaces__srv__Patrol_Response__FAIL = 0
};

/// Struct defined in srv/Patrol in the package service_interfaces.
typedef struct service_interfaces__srv__Patrol_Response
{
  /// 处理结果，SUCCESS / FAIL 取其一 （小写变量）
  int8_t result;
} service_interfaces__srv__Patrol_Response;

// Struct for a sequence of service_interfaces__srv__Patrol_Response.
typedef struct service_interfaces__srv__Patrol_Response__Sequence
{
  service_interfaces__srv__Patrol_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} service_interfaces__srv__Patrol_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SERVICE_INTERFACES__SRV__DETAIL__PATROL__STRUCT_H_
