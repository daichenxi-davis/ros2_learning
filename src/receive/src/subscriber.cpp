#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class SubscriberNode: public rclcpp::Node
{
private:
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;

	void callback(std_msgs::msg::String::SharedPtr msg)
	{
		RCLCPP_INFO(this->get_logger(),"Received: %s",msg->data.c_str());
	}
public:
	SubscriberNode():Node("receive_subscriber")
	{
		subscriber_=this->create_subscription<std_msgs::msg::String>("chatter",100,[this](const std_msgs::msg::String::SharedPtr msg){this->callback(msg);});
	}
};

int main(int argc,char *argv[])
{
	rclcpp::init(argc,argv);
	rclcpp::spin(std::make_shared<SubscriberNode>());
	rclcpp::shutdown();
}