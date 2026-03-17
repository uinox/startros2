import rclpy
from rclpy.node import Node

def main():
    rclpy.init()
    node = Node("python_node")
    node.get_logger().info('hello Python node!')
    node.get_logger().warning('hello Python node!')
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()