#include <functional>
#include <memory>
#include <string.h>
#include <string>

#include "msgs_and_srvs/msg/crust.hpp"
#include "rclcpp/rclcpp.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
public:
  MinimalSubscriber() : Node("minimal_subscriber") {
    subscription_ = this->create_subscription<msgs_and_srvs::msg::Crust>(
        "crust", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const msgs_and_srvs::msg::Crust &msg) const {
    RCLCPP_INFO(this->get_logger(), "Crust Received: '%ld %s'", msg.crust_id,
                msg.ingredient.c_str());
  }
  rclcpp::Subscription<msgs_and_srvs::msg::Crust>::SharedPtr subscription_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}