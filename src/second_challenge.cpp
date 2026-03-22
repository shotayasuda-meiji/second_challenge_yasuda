#include "second_challenge/second_challenge.hpp"
#include<stdio.h>
#include<math.h>

/*
Overall Processing Flow
1. Receiving self-position data  : Retrieve the current robot's position coordinates from the odom topic
2. Calculating Distance Traveled  : Calculate the straight-line distance from the origin
3. Decision  : Check whether it has reached 1.0 m
4. Send Command  : If it has not reached the target, proceed at 0.3m/s; if it has reached the target, send a stop command
*/

//Initial Node Configuration
SecondChallenge::SecondChallenge() : Node("SecondChallenge")
{
    cmd_vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);  // Publisher object to send velocity commands to the robot

    odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>("odom", 10, std::bind(&SecondChallenge::odometry_callback, this, std::placeholders::_1));  // Subscribe to odometry data to get robot's position

    goal_dist_ = 1.0;
    hz_ = 10;
}

// A function called when data is received from a sensor
void SecondChallenge::odometry_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
    odom_ = *msg;  // Indirectly access the pointer and store the message content
                   // When new data arrives, discard the old data and overwrite it
}

// Check if odometry data is available
// Without this function, the program might crash if it attempts to perform calculations using an empty odom_ that has not yet received any data
bool SecondChallenge::can_move()
{
    printf("value : %d\n",odom_.has_value() );
    return odom_.has_value();  // Returns true(1) if data is present, and false(0) if not
}
    
// Goal Dicision
bool SecondChallenge::is_goal()
{
    if(calc_distance() >= goal_dist_){  // Return true if the calculated distance exceeds 1.0
        printf("true\n");
        return true;
    }
    return false; 
}

// Use the Pythagorean theorem to calculate the distance from the starting point
double SecondChallenge::calc_distance()
{
    double x = odom_->pose.pose.position.x;
    double y = odom_->pose.pose.position.y;
    double dist = std::sqrt(x*x + y*y);
    printf("dist = %f\n",dist);
    return dist;
}

void SecondChallenge::run(float velocity, float omega)
{
    if(!is_goal()){  // While not at the goal
        cmd_vel_.linear.x = velocity;
        cmd_vel_.angular.z = omega;
    }else{
        cmd_vel_.linear.x = 0.0;
        cmd_vel_.angular.z = 0.0;
    }
    printf("vel = %f, ang = %f\n", cmd_vel_.linear.x, cmd_vel_.angular.z);
    cmd_vel_pub_->publish(cmd_vel_);  // Send actual movement commands to the robot
    
}

void SecondChallenge::set_cmd_vel()
{
    if (can_move()) 
        run(0.3, 0.0);
    printf("run\n");
    
}
