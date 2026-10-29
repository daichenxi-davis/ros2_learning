#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

using namespace std::chrono_literals;

class SubscriberNode: public rclcpp::Node
{
private:
	rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr subscriber_;

	void callback(geometry_msgs::msg::PoseStamped::SharedPtr msg)
	{
		RCLCPP_INFO(this->get_logger(),"Received: position(%.2f,%.2f,%.2f)",msg->pose.position.x,msg->pose.position.y,msg->pose.position.z);
	}
public:
	SubscriberNode():Node("receive_subscriber")
	{
		rclcpp::QoS qos(100);
		qos.reliability(rclcpp::ReliabilityPolicy::Reliable);
		qos.durability(rclcpp::DurabilityPolicy::Volatile);
		qos.history(rclcpp::HistoryPolicy::KeepLast);
		subscriber_=this->create_subscription<geometry_msgs::msg::PoseStamped>("chatter",qos,[this](const geometry_msgs::msg::PoseStamped::SharedPtr msg){this->callback(msg);});
	}
};

int main(int argc,char *argv[])
{
	rclcpp::init(argc,argv);
	rclcpp::spin(std::make_shared<SubscriberNode>());
	rclcpp::shutdown();
}