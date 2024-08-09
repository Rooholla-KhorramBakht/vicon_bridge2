cmake_minimum_required(VERSION 3.5)
project(vicon_bridge2)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # add_compile_options(-Wall -Wextra -Wpedantic -g)
  add_compile_options(-Wall -Wextra -Wno-pedantic -g)
endif()
add_compile_options(-Wno-pedantic -Wno-unknown-pragmas -Wno-unused-parameter)
include_directories(
  include
  ${Boost_INCLUDE_DIRS}
  vicon_sdk/DataStream
  vicon_sdk
)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread date_time) 
find_package(geometry_msgs REQUIRED)  # Add this line to find geometry_msgs
find_package(std_msgs REQUIRED)  # Add this line to find std_msgs
find_package(tf2 REQUIRED)  # Add this line to find tf2
find_package(tf2_ros REQUIRED)  # Add this line to find tf2_ros
find_package(vicon_msgs REQUIRED)  # Add this line to find tf2_ros


# Compile Vicon SDK from scratch to avoid Boost version mismatch clashes
file(GLOB_RECURSE vicon_sdk_files "${CMAKE_CURRENT_SOURCE_DIR}/vicon_sdk/**/**.cpp")
add_library(vicon_sdk ${vicon_sdk_files})
# target_compile_options(vicon_sdk PRIVATE -Wno-pedantic)
target_link_libraries(vicon_sdk PUBLIC ${Boost_LIBRARIES})


add_executable(vicon_client src/vicon_bridge2/communicator.cpp)
# target_link_libraries(vicon_client ViconDataStreamSDK_CPP ${Boost_LIBRARIES})
target_link_libraries(vicon_client vicon_sdk ${Boost_LIBRARIES})
ament_target_dependencies(vicon_client "rclcpp" "geometry_msgs" "std_msgs" "tf2" "tf2_ros" "vicon_msgs")

install(TARGETS vicon_client DESTINATION lib/${PROJECT_NAME})

# Install launch file
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
