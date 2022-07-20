""""Test suite to accompany shapes.py"""

import unittest
from q3_shapes import *

# Tests for 'Point' alone

class Test_Point(unittest.TestCase):

    def test_0_equality(self):
        p1 = Point(5.3, 7.2)
        p2 = Point(5.3, 7.2)
        p3 = Point(4.3, 8.9)
        self.assertEqual(p1, p2)
        self.assertNotEqual(p1, p3)

    def test_1_distance(self):
        # Simplest to calculate is
        # hypotenuse of 3,4,5 triangle
        p1 = Point(8.0,12.0)
        p2 = Point(11.0,16.0)  # dx, dy = 3,4
        d = p1.dist(p2)
        self.assertEqual(d, 5.0)

class Test_Shapes(unittest.TestCase):

    def setUp(self) -> None:
        self.circle_1 = Circle(Point(0.0,0.0), 5.0)
        self.circle_2 = Circle(Point(0.0, 8.0), 3.0)
        self.circle_3 = Circle(Point(0.0, 3.0), 2.0)
        self.rect_1 = Rect(Point(0.0, 0.0), Point(0.0, 5.0))
        self.rect_2 = Rect(Point(5.0, 5.0), Point(10.0,10.0))

    def test_0_verticals(self):
        self.assertTrue(self.circle_2.above(self.circle_1))
        self.assertTrue(self.circle_1.below(self.circle_2))
        self.assertTrue(self.circle_2.above(self.rect_1))
        self.assertTrue(self.rect_1.below(self.circle_2))
        self.assertFalse(self.rect_1.above(self.rect_2))
        self.assertFalse(self.circle_3.above(self.circle_1))
        self.assertFalse(self.circle_1.above(self.circle_3))

if __name__ == '__main__':
    unittest.main()
