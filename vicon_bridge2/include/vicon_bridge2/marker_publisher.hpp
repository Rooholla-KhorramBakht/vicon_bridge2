#ifndef MARKERPUBLISHER_HPP
#define MARKERPUBLISHER_HPP
#include <unistd.h>
#include "rclcpp/rclcpp.hpp"
#include "vicon_msgs/msg/markers.hpp"

// Class that allows segment data to be published in a ROS2 topic.
class MarkerPublisher
{
private:
    rclcpp::Publisher<vicon_msgs::msg::Markers>::SharedPtr marker_publisher_;
    std::string topic_name_;
    rclcpp::Node* node_;
public:
    bool is_ready = false;

    MarkerPublisher(std::string topic_name, rclcpp::Node* node)
    {
        marker_publisher_ = node->create_publisher<vicon_msgs::msg::Markers>(topic_name, 10);
        is_ready = true;
        topic_name_ = topic_name;
        node_ = node;
    }

    void publish(vicon_msgs::msg::Markers &markers)
    {
        marker_publisher_->publish(markers);
    }
};

#endif