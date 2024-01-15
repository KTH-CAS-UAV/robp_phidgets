#ifndef ROBP_PHIDGETS_ENCODERS_H
#define ROBP_PHIDGETS_ENCODERS_H

// robp_phidgets
#include <robp_phidgets/EncoderConfig.h>
#include <robp_phidgets/encoder.h>

// robp_interfaces
#include <robp_interfaces/msg/encoders.hpp>

// ROS
#include <rclcpp/rclcpp.hpp>

// STL
#include <memory>

namespace robp::phidgets
{
class Encoders : public rclcpp::Node
{
 public:
	explicit Encoders(rclcpp::NodeOptions const& options);

 private:
	void publish();

	rcl_interfaces::msg::SetParametersResult parametersCallback(
	     std::vector<rclcpp::Parameter> const& parameters);

 private:
	rclcpp::Publisher<robp_interfaces::msg::Encoders>::SharedPtr pub_;

	std::unique_ptr<Encoder> left_;
	std::unique_ptr<Encoder> right_;
};
}  // namespace robp::phidgets

#endif  // ROBP_PHIDGETS_ENCODERS_H