/**********************************************************************
 David Román Grijalbo, Jaume I University
***********************************************************************/

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <unitree_go/msg/detail/sport_mode_state__struct.hpp>
#include "common/ros2_sport_client.h"
#include "unitree_go/msg/sport_mode_state.hpp"
#include "sensor_msgs/msg/joy.hpp"

enum action  {
    MOVE,
    STOP_MOVE,
};

rclcpp::Logger my_logger = rclcpp::get_logger("my_controller");

float vx = 0.3;
float vz = 0;

/*
  MOVE:
  nlohmann::json js;
  js["x"] = vx;
  js["y"] = vy;
  js["z"] = vyaw;
*/
void JoyCallback(sensor_msgs::msg::Joy::SharedPtr msg){
     
    if (msg->buttons[3] == 1) {
        action == MOVE;       
        RCLCPP_INFO(my_logger, "Mode: MOVE");
    }

   
    else if (msg->buttons[0] == 1) {
        action == STOP_MOVE;  
        RCLCPP_INFO(my_logger, "Mode: STOP_MOVE");
    }
    else{
        action == STOP_MOVE;
        RCLCPP_INFO(my_logger, "No buttons detected");
    }
}

void RobotControl(){
    switch(action){
        case MOVE:
            sport_client.Move(req,vx,0,vz);
            break;
        case STOP_MOVE:
            sport_client.StopMove(req);
            break;
        default:
            sport_client.StopMove(req);
    }

}



unitree_api::msg::Request req; // Unitree Go2 ROS2 request message

int main(int argc, char* argv[]){
    rclcpp::init(argc,argv);
    auto node = rclcpp::Node::make_shared("controller_ros2_sport_client");

     // Servicio (cliente sport)
    sport_client = std::make_shared<SportClient>(node.get()); // the srv is waiting for:  SportClient::SportClient(rclcpp::Node *node)

    auto subscriber = node -> create_subscriber<sensor_msgs::msg::Joy>("joy",10,JoyCallback);

    while(rclcpp::ok()){
        RobotControl();
        rclcpp::spin_some(node);
    }
    rclcpp::shutdown();
    return 0;
    





}