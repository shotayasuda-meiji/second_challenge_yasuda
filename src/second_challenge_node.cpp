#include "second_challenge/second_challenge.hpp"

int main(int argc, char * argv[])
{
  // Initialize ROS 2 communication
  rclcpp::init(argc, argv);

  // Instantiate the node using a shared pointer
  std::shared_ptr<SecondChallenge> schallenge = std::make_shared<SecondChallenge>();

  // Keep the node spinning to process callback
  rclcpp::spin(schallenge);

  // Shutdown ROS 2 on exit
  rclcpp::shutdown();

  return 0;
}
