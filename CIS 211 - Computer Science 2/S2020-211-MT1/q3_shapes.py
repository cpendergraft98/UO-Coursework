"""Midterm 1 Problem 3
"""

import math

class Point:
    """A point in the Cartesian plane"""

    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y

    def __eq__(self, other: "Point") -> bool:
        assert isinstance(other, Point)
        return self.x == other.x and self.y == other.y

    def dist(self, other: "Point") -> float:
        """Standard distance formula in cartesian coordinates"""
        dx = self.x - other.x
        dy = self.y - other.y
        return math.sqrt(dx*dx + dy*dy)


class Shape:
    """Abstract base class for polygons"""

    def __init__(self):
        raise NotImplementedError("Don't instantiate Shape!")

    def y_min(self) -> float:
        raise NotImplementedError("y_min not implemented")

    def y_max(self) -> float:
        raise NotImplementedError("y_max not implemented")

    def above(self, other: "Shape") -> bool:
        return self.y_max > other.y_max

    def below(self, other: "Shape") -> bool:
        return self.y_min < other.y_min


class Circle(Shape):
    """Circle is defined by center and radius"""

    def __init__(self, center: Point, radius: float):
        self.center = center
        self.radius = radius

    def __repr__(self) -> str:
        return f"Circle({self.center}, {self.radius})"

    def y_min(self) -> float:
        return self.center.y - self.radius

    def y_max(self) -> float:
        return self.center.y + self.radius


class Rect(Shape):
    """A rectangle is defined by two opposite corners"""

    def __init__(self, ll: Point, ur: Point):
        assert ll.x <= ur.x and ll.y <= ur.y, "Invalid points for creating rect"
        self.ll = ll
        self.ur = ur

    def __repr__(self) -> str:
        return f"Rect({self.ll}, {self.rr})"

    def y_min(self) -> float:
        return self.ll.y

    def y_max(self) -> float:
        return self.ur.y