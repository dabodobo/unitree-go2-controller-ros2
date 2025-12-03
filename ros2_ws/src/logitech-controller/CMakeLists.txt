cmake_minimum_required(VERSION 3.5)
project(logitech-controller)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


include_directories(include include/common include/nlohmann)
link_directories(src)

set (
  DEPENDENCY_LIST
  unitree_go
  unitree_hg
  unitree_api
  rclcpp
  std_msgs
  rosbag2_cpp
  sensor_msgs
)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(unitree_go REQUIRED)
find_package(unitree_hg REQUIRED)
find_package(unitree_api REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosbag2_cpp REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(sensor_msgs REQUIRED)



#add_executable(record_bag src/record_bag.cpp)
#add_executable(go2_sport_client src/go2/go2_sport_client.cpp src/common/ros2_sport_client.cpp)
#target_compile_features(go2_sport_client PRIVATE cxx_std_20)


#add_executable (mando  src/go2/go2_mando.cpp src/common/ros2_sport_client.cpp)
#target_compile_features(mando PRIVATE cxx_std_20)

#ament_target_dependencies(record_bag ${DEPENDENCY_LIST})
#ament_target_dependencies(mando ${DEPENDENCY_LIST})
add_executable(controller src/controller.cpp)
target_compile_features(controller PRIVATE cxx_std_20)
ament_target_dependencies(controller ${DEPENDENCY_LIST})






#install(TARGETS g1_audio_client_example)
install(TARGETS
          controller
          DESTINATION lib/${PROJECT_NAME}
  )
 install(DIRECTORY launch
          DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()