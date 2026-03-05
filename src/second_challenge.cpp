#include "second_challenge/second_challenge.hpp"
#include<stdio.h>
#include<math.h>

SecondChallenge::SecondChallenge() : Node("SecondChallenge")
{
    cmd_vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);

    odom_sub_ = this->create_subscription<nav_msgs::msg::Odometry>("odom", 10, std::bind(&SecondChallenge::odometry_callback, this, std::placeholders::_1));

    goal_dist_ = 1.0;
    hz_ = 10;
}

void SecondChallenge::odometry_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
    odom_ = *msg;
}

bool SecondChallenge::can_move()
{
    printf("value : %d\n",odom_.has_value() );
    return odom_.has_value();
}
    

bool SecondChallenge::is_goal()
{
    if(calc_distance() >= goal_dist_){
        printf("true\n");
        return true;
    }
    return false;
}

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
    auto message = geometry_msgs::msg::Twist();
    if(!is_goal()){
        cmd_vel_.linear.x = velocity;
        cmd_vel_.angular.z = omega;
    }else{
        cmd_vel_.linear.x = 0.0;
        cmd_vel_.angular.z = 0.0;
    }
    printf("vel = %f, ang = %f\n", cmd_vel_.linear.x, cmd_vel_.linear.z);
    cmd_vel_pub_->publish(cmd_vel_);
    
}

void SecondChallenge::set_cmd_vel()
{
    if (can_move()) 
        run(0.3, 0.0);
    printf("run\n");
    
}
