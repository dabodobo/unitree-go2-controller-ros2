/**********************************************************************
 David Román Grijalbo, Jaume I University
***********************************************************************/

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <unitree_go/msg/detail/sport_mode_state__struct.hpp>
#include "common/ros2_sport_client.h"
#include "unitree_go/msg/sport_mode_state.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include <string>
#include <map>
enum ACTION  {
    MOVE,
    STOP_MOVE,
    HELLO,
};
ACTION action = STOP_MOVE;
rclcpp::Logger my_logger = rclcpp::get_logger("CONTROLLER");

float vx = 0.3;
float vz = 0;

/*
  MOVE:
  nlohmann::json js;
  js["x"] = vx;
  js["y"] = vy;
  js["z"] = vyaw;
*/




std::map<int, std::string> msgs = {
    {0, "Mode: STOP_MOVE"},
    {1, "Moving Straight"},
    {2, "Moving Backwards"},
    {3, "Moving Left"},
    {4, "Moving Right"},
    {5, "HI !"}
};

int last_msg = 0;
int msg_type = 0;
void msg_control(int &msg){
    if(msg != last_msg){
        RCLCPP_INFO(my_logger,msgs[msg]);
        last_msg = msg;
    }
}
void update_velocities(float x, float z){
    vx = x;
    vz = z;
}
void JoyCallback(sensor_msgs::msg::Joy::SharedPtr msg){
     
    //go ahead
    if (msg->axes[1] > 0.4) {
        action = MOVE;  
        update_velocities(0.3,0);   
        msg_type = 1;
        msg_control(msg_type);
    }

    // backwards
    else if (msg->axes[1] < -0.4) {
        action = MOVE;       
        update_velocities(-0.3,0);  
        msg_type = 2;
        msg_control(msg_type);
    }
    // left 
    else if(msg->axes[3] > 0.4) {
        action = MOVE;  
        update_velocities(0,0.6);   
        msg_type = 3;
        msg_control(msg_type);
    }
    
    //right
    else if(msg->axes[3] < -0.4) {
        action = MOVE;  
        update_velocities(0,-0.6);   
        msg_type = 4;
        msg_control(msg_type);
    }



   
    else if (msg->buttons[0] == 1) {
        action = STOP_MOVE;  
        msg_type = 0;
        msg_control(msg_type);
    }

    else if (msg->buttons[1] == 1) {
        action = HELLO;  
        msg_type = 5;
        msg_control(msg_type);
    }
    else{
        action = STOP_MOVE;
        //RCLCPP_INFO(my_logger, "No buttons detected");
        last_msg = 0;
    }
}

void RobotControl(unitree_api::msg::Request req,std::shared_ptr<SportClient> sport_client){
    switch(action){
        case MOVE:
            sport_client->Move(req,vx,0,vz);
            break;
        case STOP_MOVE:
            sport_client->StopMove(req);
            break;
        case HELLO:
            sport_client->Hello(req);
            break;
        default:
            sport_client->StopMove(req);
            break;
    }

}



unitree_api::msg::Request req; // Unitree Go2 ROS2 request message
std::shared_ptr<SportClient> sport_client;

int main(int argc, char* argv[]){
    rclcpp::init(argc,argv);
    auto node = rclcpp::Node::make_shared("controller_ros2_sport_client");

     // Servicio (cliente sport)
    sport_client = std::make_shared<SportClient>(node.get()); // the srv is waiting for:  SportClient::SportClient(rclcpp::Node *node)

    auto subscriber = node -> create_subscription<sensor_msgs::msg::Joy>("joy",10,JoyCallback);

    while(rclcpp::ok()){
        RobotControl(req,sport_client);
        rclcpp::spin_some(node);
    }
    rclcpp::shutdown();
    return 0;
    





}