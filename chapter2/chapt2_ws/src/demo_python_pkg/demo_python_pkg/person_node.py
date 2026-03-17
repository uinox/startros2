import rclpy
from rclpy.node import Node

class PersonNode(Node):
    def __init__(self, node_name: str, name: str, age: int) -> None:
        super().__init__(node_name)
        # print("PersonNode's __init__ is called")
        self.age = age
        self.name = name

    def eat(self, food_name: str):
        self.get_logger().info(f' my name is {self.name}, I am {self.age} years old, I am eating {food_name}')
        # print(f'my name is {self.name}, I am {self.age} years old, I am eating {food_name}')
        
def main():
    rclpy.init()
    node = PersonNode('person_node', 'zhangsan', 18)
    node.eat('apple')
    rclpy.spin(node)
    rclpy.shutdown()