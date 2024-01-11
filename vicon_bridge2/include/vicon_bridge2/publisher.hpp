#ifndef PUBLISHER_HPP
#define PUBLISHER_HPP
#include <unistd.h>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/msg/transform_stamped.hpp>
// #include "pycon/vicon.hpp"

// Struct used to hold segment data to transmit to the Publisher class.
struct PositionStruct
{
    double translation[3];
    double rotation[4];
    std::string subject_name;
    std::string segment_name;
    std::string translation_type;
    unsigned int frame_number;
    // We also need when we got the data
    unsigned long time_sec;
    unsigned long time_nsec;
} typedef PositionStruct;


// Class that allows segment data to be published in a ROS2 topic.
class Publisher
{
private:
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pose_publisher_;
    std::string topic_name_;
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    rclcpp::Node* node_;
public:
    bool is_ready = false;

    // Publisher(std::string topic_name, rclcpp::Node* node);

    Publisher(std::string topic_name, rclcpp::Node* node)
    {
        pose_publisher_ = node->create_publisher<geometry_msgs::msg::PoseStamped>(topic_name, 10);
        is_ready = true;
        topic_name_ = topic_name;
        tf_broadcaster_ =
        std::make_unique<tf2_ros::TransformBroadcaster>(node);
        node_ = node;
    }

    // Publishes the given position in the ROS2 topic whose name is indicated in
    // the constructor.
    void publish(PositionStruct p)
    {
        float q_norm = p.rotation[0]*p.rotation[0] + p.rotation[1]*p.rotation[1] + p.rotation[2]*p.rotation[2] + p.rotation[3]*p.rotation[3];
        if(q_norm > 0.9999 && q_norm < 1.0001)
        {
            // Send stamped pose messages
            auto pose_msg = std::make_shared<geometry_msgs::msg::PoseStamped>();  
            pose_msg->header.stamp = node_->get_clock()->now();
            pose_msg->header.frame_id = topic_name_;
            pose_msg->pose.position.x = p.translation[0]/1000.0;
            pose_msg->pose.position.y = p.translation[1]/1000.0;
            pose_msg->pose.position.z = p.translation[2]/1000.0;
            pose_msg->pose.orientation.x = p.rotation[0];
            pose_msg->pose.orientation.y = p.rotation[1];
            pose_msg->pose.orientation.z = p.rotation[2];
            pose_msg->pose.orientation.w = p.rotation[3];
            pose_publisher_->publish(*pose_msg);

            // Send TF2 messages
            geometry_msgs::msg::TransformStamped t;
            t.header.stamp = node_->get_clock()->now();
            t.header.frame_id = "vicon/World";
            t.child_frame_id = topic_name_;
            t.transform.translation.x = p.translation[0]/1000.0;
            t.transform.translation.y = p.translation[1]/1000.0;
            t.transform.translation.z = p.translation[2]/1000.0;
            t.transform.rotation.x = p.rotation[0];
            t.transform.rotation.y = p.rotation[1];
            t.transform.rotation.z = p.rotation[2];
            t.transform.rotation.w = p.rotation[3];
            tf_broadcaster_->sendTransform(t);
        }
    }
};

#endif