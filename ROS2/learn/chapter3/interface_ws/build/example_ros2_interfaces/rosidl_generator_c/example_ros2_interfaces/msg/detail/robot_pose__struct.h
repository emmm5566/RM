// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from example_ros2_interfaces:msg/RobotPose.idl
// generated code does not contain a copyright notice

#ifndef EXAMPLE_ROS2_INTERFACES__MSG__DETAIL__ROBOT_POSE__STRUCT_H_
#define EXAMPLE_ROS2_INTERFACES__MSG__DETAIL__ROBOT_POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'STATUS_MOVEING'.
enum
{
  example_ros2_interfaces__msg__RobotPose__STATUS_MOVEING = 1ul
};

/// Constant 'STATUS_STOP'.
enum
{
  example_ros2_interfaces__msg__RobotPose__STATUS_STOP = 2ul
};

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.h"

/// Struct defined in msg/RobotPose in the package example_ros2_interfaces.
typedef struct example_ros2_interfaces__msg__RobotPose
{
  uint32_t status;
  geometry_msgs__msg__Pose pose;
} example_ros2_interfaces__msg__RobotPose;

// Struct for a sequence of example_ros2_interfaces__msg__RobotPose.
typedef struct example_ros2_interfaces__msg__RobotPose__Sequence
{
  example_ros2_interfaces__msg__RobotPose * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} example_ros2_interfaces__msg__RobotPose__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // EXAMPLE_ROS2_INTERFACES__MSG__DETAIL__ROBOT_POSE__STRUCT_H_
