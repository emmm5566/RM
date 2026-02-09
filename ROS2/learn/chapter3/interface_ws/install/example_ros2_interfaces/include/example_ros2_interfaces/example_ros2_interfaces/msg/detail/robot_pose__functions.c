// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from example_ros2_interfaces:msg/RobotPose.idl
// generated code does not contain a copyright notice
#include "example_ros2_interfaces/msg/detail/robot_pose__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `pose`
#include "geometry_msgs/msg/detail/pose__functions.h"

bool
example_ros2_interfaces__msg__RobotPose__init(example_ros2_interfaces__msg__RobotPose * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // pose
  if (!geometry_msgs__msg__Pose__init(&msg->pose)) {
    example_ros2_interfaces__msg__RobotPose__fini(msg);
    return false;
  }
  return true;
}

void
example_ros2_interfaces__msg__RobotPose__fini(example_ros2_interfaces__msg__RobotPose * msg)
{
  if (!msg) {
    return;
  }
  // status
  // pose
  geometry_msgs__msg__Pose__fini(&msg->pose);
}

bool
example_ros2_interfaces__msg__RobotPose__are_equal(const example_ros2_interfaces__msg__RobotPose * lhs, const example_ros2_interfaces__msg__RobotPose * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__are_equal(
      &(lhs->pose), &(rhs->pose)))
  {
    return false;
  }
  return true;
}

bool
example_ros2_interfaces__msg__RobotPose__copy(
  const example_ros2_interfaces__msg__RobotPose * input,
  example_ros2_interfaces__msg__RobotPose * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // pose
  if (!geometry_msgs__msg__Pose__copy(
      &(input->pose), &(output->pose)))
  {
    return false;
  }
  return true;
}

example_ros2_interfaces__msg__RobotPose *
example_ros2_interfaces__msg__RobotPose__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  example_ros2_interfaces__msg__RobotPose * msg = (example_ros2_interfaces__msg__RobotPose *)allocator.allocate(sizeof(example_ros2_interfaces__msg__RobotPose), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(example_ros2_interfaces__msg__RobotPose));
  bool success = example_ros2_interfaces__msg__RobotPose__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
example_ros2_interfaces__msg__RobotPose__destroy(example_ros2_interfaces__msg__RobotPose * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    example_ros2_interfaces__msg__RobotPose__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
example_ros2_interfaces__msg__RobotPose__Sequence__init(example_ros2_interfaces__msg__RobotPose__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  example_ros2_interfaces__msg__RobotPose * data = NULL;

  if (size) {
    data = (example_ros2_interfaces__msg__RobotPose *)allocator.zero_allocate(size, sizeof(example_ros2_interfaces__msg__RobotPose), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = example_ros2_interfaces__msg__RobotPose__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        example_ros2_interfaces__msg__RobotPose__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
example_ros2_interfaces__msg__RobotPose__Sequence__fini(example_ros2_interfaces__msg__RobotPose__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      example_ros2_interfaces__msg__RobotPose__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

example_ros2_interfaces__msg__RobotPose__Sequence *
example_ros2_interfaces__msg__RobotPose__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  example_ros2_interfaces__msg__RobotPose__Sequence * array = (example_ros2_interfaces__msg__RobotPose__Sequence *)allocator.allocate(sizeof(example_ros2_interfaces__msg__RobotPose__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = example_ros2_interfaces__msg__RobotPose__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
example_ros2_interfaces__msg__RobotPose__Sequence__destroy(example_ros2_interfaces__msg__RobotPose__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    example_ros2_interfaces__msg__RobotPose__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
example_ros2_interfaces__msg__RobotPose__Sequence__are_equal(const example_ros2_interfaces__msg__RobotPose__Sequence * lhs, const example_ros2_interfaces__msg__RobotPose__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!example_ros2_interfaces__msg__RobotPose__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
example_ros2_interfaces__msg__RobotPose__Sequence__copy(
  const example_ros2_interfaces__msg__RobotPose__Sequence * input,
  example_ros2_interfaces__msg__RobotPose__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(example_ros2_interfaces__msg__RobotPose);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    example_ros2_interfaces__msg__RobotPose * data =
      (example_ros2_interfaces__msg__RobotPose *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!example_ros2_interfaces__msg__RobotPose__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          example_ros2_interfaces__msg__RobotPose__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!example_ros2_interfaces__msg__RobotPose__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
