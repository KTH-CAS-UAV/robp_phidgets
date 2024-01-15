cmake_minimum_required(VERSION 3.8)

project(robp_phidgets
  VERSION 1.0.0
  DESCRIPTION ""
  LANGUAGES C CXX
)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(robp_interfaces REQUIRED)
find_package(angles REQUIRED)
find_package(imu_filter_magwick REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

include_directories(include)

# create ament index resource which references the libraries in the binary dir
set(node_plugins "")

add_library(encoders_component SHARED 
  src/encoders.cpp 
  src/encoder.cpp
)
ament_target_dependencies(encoders_component
  "rclcpp"
  "rclcpp_components"
)
rclcpp_components_register_nodes(encoders_component "robp::phidgets::Encoders")
set(node_plugins "${node_plugins}robp::phidgets::Encoders;$<TARGET_FILE:encoders_component>\n")

add_library(robp_phidgets_util SHARED src/util.cpp src/error.cpp)
ament_target_dependencies(robp_phidgets_util
  "rclcpp"
)
rclcpp_components_register_nodes(robp_phidgets_util "robp::phidgets::Util")
set(node_plugins "${node_plugins}robp::phidgets::Util;$<TARGET_FILE:robp_phidgets_util>\n")

add_compile_options(-std=c++17)
set(default_build_type "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
    STRING "Choose the type of build." FORCE)

  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
