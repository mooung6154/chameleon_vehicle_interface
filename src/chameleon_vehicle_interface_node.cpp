#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <cmath>

class ChameleonVehicleInterface : public rclcpp::Node
{
public:
  ChameleonVehicleInterface() : Node("chameleon_vehicle_interface")
  {
    this->declare_parameter("wheel_base", 0.5);
    this->declare_parameter("wheel_tread", 0.4);

    wheel_base_  = this->get_parameter("wheel_base").as_double();
    wheel_tread_ = this->get_parameter("wheel_tread").as_double();

    sub_cmd_ = this->create_subscription<geometry_msgs::msg::Twist>(
      "/cmd_vel", 10,
      std::bind(&ChameleonVehicleInterface::onControlCmd, this,
                std::placeholders::_1));

    RCLCPP_INFO(this->get_logger(), "Chameleon Vehicle Interface 시작!");
  }

private:
  void computeWheelAngles(
    double delta,
    double & fl, double & fr,
    double & rl, double & rr)
  {
    if (std::abs(delta) < 1e-6) {
      fl = fr = rl = rr = 0.0;
      return;
    }
    double R = wheel_base_ / std::tan(delta);
    fl = std::atan(wheel_base_ / (R - wheel_tread_ / 2.0));
    fr = std::atan(wheel_base_ / (R + wheel_tread_ / 2.0));
    rl = -fl;
    rr = -fr;
  }

  void onControlCmd(const geometry_msgs::msg::Twist::SharedPtr msg)
  {
    double delta = msg->angular.z;
    double speed = msg->linear.x;

    double fl, fr, rl, rr;
    computeWheelAngles(delta, fl, fr, rl, rr);

    RCLCPP_INFO(this->get_logger(),
      "\n[입력]\n"
      "  조향각: %.4f rad (%.2f deg)\n"
      "  속도:   %.3f m/s\n"
      "[4WS 변환 출력]\n"
      "  FL: %.4f rad (%6.2f deg)\n"
      "  FR: %.4f rad (%6.2f deg)\n"
      "  RL: %.4f rad (%6.2f deg)\n"
      "  RR: %.4f rad (%6.2f deg)",
      delta, delta * 180.0 / M_PI, speed,
      fl, fl * 180.0 / M_PI,
      fr, fr * 180.0 / M_PI,
      rl, rl * 180.0 / M_PI,
      rr, rr * 180.0 / M_PI);
  }

  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr sub_cmd_;
  double wheel_base_;
  double wheel_tread_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ChameleonVehicleInterface>());
  rclcpp::shutdown();
  return 0;
}
