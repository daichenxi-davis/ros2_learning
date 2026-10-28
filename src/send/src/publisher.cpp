#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class PublisherNode: public rclcpp::Node
{
private:
	int count;
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
	rclcpp::TimerBase::SharedPtr timer_;

	void callback()
	{
		auto msg=std_msgs::msg::String();
		msg.data="Hello, count:"+std::to_string(count++);
		RCLCPP_INFO(this->get_logger(),"Publishing: %s",msg.data.c_str());
		publisher_->publish(msg);
	}
public:
	PublisherNode():Node("send_publisher"),count(0)
	{
		publisher_=this->create_publisher<std_msgs::msg::String>("chatter",100);
		timer_=this->create_wall_timer(500ms,[this](){this->callback();});
	}
};

int main(int argc,char *argv[])
{
	rclcpp::init(argc,argv);
	rclcpp::spin(std::make_shared<PublisherNode>());
	rclcpp::shutdown();
}