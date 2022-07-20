"""Test suite for intervals.py"""

import unittest
from q1_intervals import *

class Test_0_Interval(unittest.TestCase):

    def test_0_Interval_magic(self):
        """Magic methods __str__ and __repr__"""
        int_0 = Interval(5, 7)
        self.assertEqual(str(int_0), "[5, 7]")
        self.assertEqual(repr(int_0), "Interval(5, 7)")

    def test_1_Interval_contains(self):
        """Closed intervals contain low .. high"""
        int_0 = Interval(5, 7)
        # Properly within the interval
        self.assertTrue(int_0.contains(6))
        # Closed intervals include their endpoints
        self.assertTrue(int_0.contains(5))
        self.assertTrue(int_0.contains(7))
        # But not everything
        self.assertFalse(int_0.contains(4))
        self.assertFalse(int_0.contains(8))

class Test_1_Intervals(unittest.TestCase):
    """A sequence of intervals contains the things
    that any of the element intervals contain.
    """

    def test_0_Intervals_empty(self):
        """Empty list of intervals contains nothing"""
        intervals_0 = IntervalCollection()
        self.assertFalse(intervals_0.contains(4))

    def test_1_Intervals_single(self):
        intervals_0 = IntervalCollection()
        intervals_0.append(Interval(3,7))
        self.assertTrue(intervals_0.contains(4))
        self.assertTrue(intervals_0.contains(3))
        self.assertTrue(intervals_0.contains(7))
        self.assertFalse(intervals_0.contains(2))
        self.assertFalse(intervals_0.contains(19))

    def test_2_Intervals_several(self):
        intervals_0 = IntervalCollection()
        intervals_0.append(Interval(-5, 4))
        intervals_0.append(Interval(7,12))
        intervals_0.append(Interval(13, 17))
        intervals_0.append(Interval(-12, -4))
        self.assertTrue(intervals_0.contains(-3))
        self.assertTrue(intervals_0.contains(0))
        self.assertTrue(intervals_0.contains(14))
        self.assertTrue(intervals_0.contains(9))
        self.assertFalse(intervals_0.contains(-35))
        self.assertFalse(intervals_0.contains(5))
        self.assertFalse(intervals_0.contains(19))


if __name__ == "__main__":
    unittest.main()



