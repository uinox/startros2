#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
// turtlesim已经不用了，新版本使用turtlesim_msgs替代
#include "turtlesim_msgs/msg/pose.hpp"

class TurtleController : public rclcpp::Node {
public:
    TurtleController() : Node("turtle_controller") {
            velocity_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
            pose_subscription_ = this->create_subscription<turtlesim_msgs::msg::Pose>("/turtle1/pose", 10, std::bind(&TurtleController::on_pose_received_, this, std::placeholders::_1));
    }
private:
    void on_pose_received_(const turtlesim_msgs::msg::Pose::SharedPtr pose) {
        //
        auto message = geometry_msgs::msg::Twist();
        // 1. 记录当前位置
        double current_x = pose->x;
        double current_y = pose->y;
        RCLCPP_INFO(this->get_logger(), " 当前位置：(x=%f,y=%f)", current_x, current_y);
        // 2. 计算与目标之间的距离，以及当前海龟朝向的角度差
        double distance = 
            std::sqrt((target_x_ - current_x) * (target_x_ - current_x) + 
            (target_y_ - current_y) * (target_y_ - current_y));
        double angle = 
            std::atan2(target_y_ - current_y, target_x_ - current_x) - pose->theta;

        // 3. 控制策略：距离大于0.1继续运动，角度差大于0.2则原地旋转，否则直行
        if(distance > 0.1) {
            if(fabs(angle) > 0.2) {
                message.angular.z = fabs(angle);
            } else {
                message.linear.x = k_ * distance;
            }
        }

        // 4. 限制最大值并发布消息
        if(message.linear.x > max_speed_) {
            message.linear.x = max_speed_;
        }
        velocity_publisher_->publish(message);
    }
private:
    rclcpp::Subscription<turtlesim_msgs::msg::Pose>::SharedPtr pose_subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher_;
    double target_x_{1.0};
    double target_y_{1.0};
    double k_{1.0};
    double max_speed_{3.0};
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleController>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}