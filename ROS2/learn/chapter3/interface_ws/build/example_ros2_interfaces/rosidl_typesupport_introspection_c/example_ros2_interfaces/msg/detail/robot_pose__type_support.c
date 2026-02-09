// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from example_ros2_interfaces:msg/RobotPose.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "example_ros2_interfaces/msg/detail/robot_pose__rosidl_typesupport_introspection_c.h"
#include "example_ros2_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "example_ros2_interfaces/msg/detail/robot_pose__functions.h"
#include "example_ros2_interfaces/msg/detail/robot_pose__struct.h"


// Include directives for member types
// Member `pose`
#include "geometry_msgs/msg/pose.h"
// Member `pose`
#include "geometry_msgs/msg/detail/pose__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void example_ros2_interfaces__msg__RobotPose__rosidl_typesupport_introspection_c__RobotPose_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  example_ros2_interfaces__msg__RobotPose__init(message_memory);
}

void example_ros2_interfaces__msg__RobotPose__rosidl_typesupport_introspection_c__RobotPose_fini_function(void * message_memory)
{
  example_ros2_interfaces__msg__RobotPose__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember example_ros2_interfaces__msg__RobotPose__rosidl_typesupport_introspection_c__RobotPose_message_member_array[2] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(example_ros2_interfaces__msg__RobotPose, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pose",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(example_ros2_interfaces__msg__RobotPose, pose),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers example_ros2_interfaces__msg__RobotPose__rosidl_typesupport_introspection_c__RobotPose_message_members = {
  "example_ros2_interfaces__msg",  // message namespace
  "RobotPose",  // message name
  2,  // number of fields
  sizeof(example_ros2_interfaces__msg__RobotPose),
  example_ros2_interfaces__msg__RobotPose__rosidl_typesupport_introspection_c__RobotPose_message_member_array,  // message members
  example_ros2_interfaces__msg__RobotPose__rosidl_typesupport_introspection_c__RobotPose_init_function,  // function to initialize message memory (memory has to be allocated)
  example_ros2_interfaces__msg__RobotPose__rosidl_typesupport_introspection_c__RobotPose_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t example_ros2_interfaces__msg__RobotPose__rosidl_typesupport_introspection_c__RobotPose_message_type_support_handle = {
  0,
  &example_ros2_interfaces__msg__RobotPose__rosidl_typesupport_introspection_c__RobotPose_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_example_ros2_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, example_ros2_interfaces, msg, RobotPose)() {
  example_ros2_interfaces__msg__RobotPose__rosidl_typesupport_introspection_c__RobotPose_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Pose)();
  if (!example_ros2_interfaces__msg__RobotPose__rosidl_typesupport_introspection_c__RobotPose_message_type_support_handle.typesupport_identifier) {
    example_ros2_interfaces__msg__RobotPose__rosidl_typesupport_introspection_c__RobotPose_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &example_ros2_interfaces__msg__RobotPose__rosidl_typesupport_introspection_c__RobotPose_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
