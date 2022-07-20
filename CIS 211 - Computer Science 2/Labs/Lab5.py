class Node:

    def __init__(self, value: int):
        self.value = value

    def sum(self):
        raise NotImplementedError("Sum is not implemented.")

    def __str__(self):
        raise NotImplementedError("__str__ is not implemented")

class Leaf(Node):

    def __init__(self, value: int):
        super().__init__(value)

    # Base Case
    def sum(self):
        return self.value

    def __str__(self) -> str:
        return f"{self.value}"

    def copy(self):
        return Leaf(self.value)

    def deepcopy(self):
        return Leaf(self.value)

class Internal(Node):

    def __init__(self, value: int, left: "Node", right: "Node"):
        super().__init__(value)
        self.left = left
        self.right = right

    # Recursive Case
    def sum(self):
        return self.value + self.left.sum() + self.right.sum()

    def __str__(self) -> str:
        return f"<{self.value}, {self.left}, {self.right}>"

    def copy(self):
        return Internal(self.value, self.left, self.right)

    def deepcopy(self):
        return Internal(self.value, self.left.deepcopy(), self.right.deepcopy())


def main():
    l1 = Leaf(3)
    print(l1)
    l2 = Leaf(6)
    l3 = Leaf(9)
    i = Internal(7, l2, l3)
    print(i)
    root = Internal(5, l1, i)
    print(root.sum())
    print(root)
    shallow = root.copy()
    deep = root.deepcopy()
    deep.right.value = 8
    print("deep after changing deep:", deep)
    print("root after changing deep:", root)
    shallow.right.value = 8
    print("shallow after changing shallow:", shallow)
    print("root after chagning shallow:", root)

if __name__ == "__main__":
    main()