/**********************************************************************
 David Román, Jaume I University
***********************************************************************/

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <thread>
#include <unitree_go/msg/detail/sport_mode_state__struct.hpp>
#include "common/ros2_sport_client.h"
#include "unitree_go/msg/sport_mode_state.hpp"
#include "sensor_msgs/msg/joy.hpp"




int main(int argc, char* argv[]){
    rclcpp::init(argc,argv)
    auto node = rclcpp::Node::make_shared("controller")
    auto subscriber = node -> create_publisher<sensor_msgs::msg::Joy>("joy",10,JoystickHandler)





}