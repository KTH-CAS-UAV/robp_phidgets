#ifndef ROBP_PHIDGETS_ENCODER_NODELET_H
#define ROBP_PHIDGETS_ENCODER_NODELET_H

// robp_phidgets
#include <robp_phidgets/encoders.h>

// ROS
#include <rclcpp/rclcpp.hpp>

// STL
#include <memory>

namespace robp::phidgets
{
class EncodersNode : public rclcpp::Node
{
 public:
	explicit EncodersNode(rclcpp::NodeOptions const& options);

 private:
	std::unique_ptr<Encoders> encoders_;
};
}  // namespace robp::phidgets

#endif  // ROBP_PHIDGETS_ENCODER_NODELET_H