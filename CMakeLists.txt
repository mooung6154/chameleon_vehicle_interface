cmake_minimum_required(VERSION 3.8)
project(chameleon_vehicle_interface)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(chameleon_vehicle_interface_node
  src/chameleon_vehicle_interface_node.cpp)

ament_target_dependencies(chameleon_vehicle_interface_node
  rclcpp
  geometry_msgs)

install(TARGETS chameleon_vehicle_interface_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
