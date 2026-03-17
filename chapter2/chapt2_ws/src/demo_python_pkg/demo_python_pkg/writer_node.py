import rclpy
from demo_python_pkg.person_node import PersonNode

class WriterNode(PersonNode):
    def __init__(self, node_name: str,name: str, age: int, book: str) -> None:
        super().__init__(node_name, name, age)
        print("WriterNode's __init__ is called")
        self.book = book

def main():
    rclpy.init()
    node = WriterNode('writer_node', 'lisi', 30, 'Jane Eyre')
    node.eat('banana')
    rclpy.spin(node)
    rclpy.shutdown()