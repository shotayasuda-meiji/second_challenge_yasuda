
#ifndef FIRST_CHALLENGE_HPP
#define FIRST_CHALLENGE_HPP

#include <rclcpp/rclcpp.hpp>
#include <functional> 
#include <memory>     
#include <optional> 

#include <sensor_msgs/msg/laser_scan.hpp>  // Settings for using LiDAR data to measure distances to surrounding obstacles
#include <geometry_msgs/msg/twist.hpp>  // Settings for controlling the robot's velocity

class SecondChallenge : public rclcpp::Node
{
    public:
        SecondChallenge();

        // Callback functions
        void timer_callback();  // A function for performing a task at regular intervals
        void scan_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg);  // A function that runs when data is received from LiDAR

        // Logic functions
        bool can_move();  // Returns true if sensor data is ready    
        bool is_goal();  // Returns true if target is reached
        double calc_distance();  // Calculate distance to the target
        void run(float velocity, float omega); 
        void set_cmd_vel();  // Determine and publish velocity

        // Configuration and Data
        int time = 0;
        int hz_ = 10;  // Control loop frequency
        double goal_dist_ = 1.0;  // Target distance
        double velocity_ = 0.4;  // Default linear velocity
        std::optional<sensor_msgs::msg::LaserScan> scan_; 
        geometry_msgs::msg::Twist cmd_vel_;

        // ROS 2 Interfaces
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_sub_;       
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_; 
};


#endif  