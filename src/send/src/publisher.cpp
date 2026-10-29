#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

using namespace std::chrono_literals;

class PublisherNode: public rclcpp::Node
{
private:
	int count;
	rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_;
	rclcpp::TimerBase::SharedPtr timer_;

	void callback()
	{
		auto msg=geometry_msgs::msg::PoseStamped();
		msg.header.stamp=this->get_clock()->now();
		msg.header.frame_id="map";
        msg.pose.position.x=(++count)*0.1;
        msg.pose.position.y=0.5;
        msg.pose.position.z=0.0;
        double yaw=M_PI/4;
        msg.pose.orientation.x=0.0;
        msg.pose.orientation.y=0.0;
        msg.pose.orientation.z=sin(yaw/2);
        msg.pose.orientation.w=cos(yaw/2);
		RCLCPP_INFO(this->get_logger(),"Publishing: position(%.2f,%.2f), time:%d",msg.pose.position.x,msg.pose.position.y,count);
		publisher_->publish(msg);
	}

public:
	PublisherNode():Node("send_publisher")
	{
		this->declare_parameter("start",0);
		count=this->get_parameter("start").as_int();
		rclcpp::QoS qos(100);
		qos.reliability(rclcpp::ReliabilityPolicy::Reliable);
		qos.durability(rclcpp::DurabilityPolicy::Volatile);
		qos.history(rclcpp::HistoryPolicy::KeepLast);
		publisher_=this->create_publisher<geometry_msgs::msg::PoseStamped>("chatter",qos);
		timer_=this->create_wall_timer(500ms,[this](){this->callback();});
	}
};

int main(int argc,char *argv[])
{
	rclcpp::init(argc,argv);
	rclcpp::spin(std::make_shared<PublisherNode>());
	rclcpp::shutdown();
}