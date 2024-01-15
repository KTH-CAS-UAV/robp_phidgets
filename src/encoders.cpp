// robp_phidgets
#include <robp_phidgets/encoders.h>

namespace robp::phidgets
{
Encoders::Encoders(rclcpp::NodeOptions const& options) : Node("encoders", options)
{
	this->declare_parameter("left_port", int{0});
	this->declare_parameter("right_port", int{0});
	this->declare_parameter("timeout", int(PHIDGET_TIMEOUT_DEFAULT));
	this->declare_parameter("data_rate", double{20.0});
	this->declare_paramter("position_change_trigger", int{0});

	int      port_left         = this->get_parameter("left_port").as_int();
	int      port_right        = this->get_parameter("right_port").as_int();
	uint32_t attach_timeout_ms = this->get_parameter("timeout").as_int();

	if (port_left == port_right) {
		RCLCPP_FATAL(this->get_logger(), "Left and right port cannot be the same");
		exit(1);
	}

	pub_ = create_publisher<robp_interfaces::msg::Encoders>("encoders", 1);

	left_  = std::make_unique<Encoder>(port_left, attach_timeout_ms,
                                    std::bind(&Encoders::publish, this));
	right_ = std::make_unique<Encoder>(port_right, attach_timeout_ms,
	                                   std::bind(&Encoders::publish, this));

	this->set_on_parameters_set_callback(
	    std::bind(&Encoders::parametersCallback, this, std::placeholders::_1));
}

void Encoders::publish()
{
	if (!left_ || !right_) {
		return;
	}

	auto msg = std::make_unique<robp_interfaces::msg::Encoders>();
	// msg->header.stamp

	msg->delta_encoder_left  = left_->change();
	msg->encoder_left        = left_->position();
	msg->delta_encoder_right = -right_->change();
	msg->encoder_right       = -right_->position();

	pub_->publish(std::move(msg));
}

rcl_interfaces::msg::SetParametersResult Encoders::parametersCallback(
    std::vector<rclcpp::Parameter> const& parameters)
{
	rcl_interfaces::msg::SetParametersResult result;
	result.successful = true;
	result.reason     = "success";
	for (auto const& parameter : parameters) {
		if ("data_rate" == parameter.get_name() &&
		    rclcpp::ParameterType::PARAMETER_DOUBLE == parameter.get_type()) {
			double data_rate = parameter.as_double();
			left_->setDataRate(data_rate);
			right_->setDataRate(data_rate);
		} else if ("position_change_trigger" == parameter.get_name() &&
		           rclcpp::ParameterType::PARAMETER_INT == parameter.get_type()) {
			int position_change_trigger = parameter.as_int();
			left_->setPositionChangeTrigger(position_change_trigger);
			right_->setPositionChangeTrigger(position_change_trigger);
		}
	}
	return result;
}
}  // namespace robp::phidgets