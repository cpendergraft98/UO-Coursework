class Point:
    def __init__(self, x: int, y: int):
        "Creates a Point (x,y)"
        self.x = x
        self.y = y

    def move(self, dx: int, dy: int):
        "Enables the movement of the Point by x+dx and y+dy."
        self.x += dx
        self.y += dy

    def __eq__(self, Point):
        "Enables the testing of equality between two Points."
        if (self.x == Point.x) and (self.y == Point.y):
            return True
        else:
            return False

    def __str__(self):
        "Creates an understandable way to print the Point."
        return f"({self.x}, {self.y})"