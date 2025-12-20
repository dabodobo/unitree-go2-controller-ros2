Hi ! I'm David Román, student from Universitat Jaume I and member of RobInLab researching group.

This project was motivated by the desire to test movement using a controller and the ROS2 interface incorporated into Go2 Unitree robots.
For now, the robot moves smoothly using the joysticks on the controller. In addition, this project can be scaled up to send different movement commands remotely. 

# Requeriments
It is important to have the official ROS2 interface from Unitree installed for it to work correctly. In addition, you must initially run source, although you can skip this step if you put it directly in ~/.bashrc.

[Unitree - ROS2](https://support.unitree.com/home/en/developer/ROS2_service)

# Installation
The first step is to send the package to our robot:

    scp -r <github_pkg> unitree@<x.x.x.x>:/home/unitree 

Now let's go to our workspace.

    cd unitree-go2-logitech-controller/ros2_ws

We compiled the package
    
    colcon build 

Make source:
    
    source install/setup.bash

Finally we launch the program that program that reads the joysticks and publish the movement of our robot:

    ros2 launch logitech-controler controller.launch.py

