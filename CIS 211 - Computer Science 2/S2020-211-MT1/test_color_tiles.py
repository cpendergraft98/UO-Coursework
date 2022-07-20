"""Test suite to accompany color_tiles.py"""

import unittest
from q2_color_tiles import *

class Test_0_Tile(unittest.TestCase):
    """Tests of the Tile class alone"""
    def setUp(self) -> None:
        self.t1 = Tile(Color.red)
        self.t2 = Tile(Color.blue)
        self.t3 = Tile(Color.red)
        self.t4 = Tile(Color.blue)

    def test_0_str(self):
        """Abbreviated tile names: First letter of color"""
        self.assertEqual(str(self.t1), "r")
        self.assertEqual(str(self.t2), "b")

    def test_1_eq(self):
        """Tiles of the same color are equal"""
        self.assertEqual(self.t1,self.t3)
        self.assertEqual(self.t2,self.t4)

    def test_2_neq(self):
        """Tiles of different colors are not equal"""
        self.assertNotEqual(self.t1,self.t2)
        self.assertNotEqual(self.t3,self.t4)


class Test_1_Row(unittest.TestCase):

    def setUp(self) -> None:
        self.r0 = Row()   # Empty row
        self.r1 = Row()   # Row built up with 'append'
        self.r1.append(Tile(Color.red))
        self.r1.append(Tile(Color.red))
        self.r1.append(Tile(Color.blue))
        self.r1.append(Tile(Color.blue))
        # Identical row built from string
        self.r2 = Row()
        self.r2.append("b")  # This should be overridden
        self.r2.from_abbreviation("rrbb")
        # Row with different tile colors
        self.r3 = Row()
        self.r3.from_abbreviation("rbbr")
        # Row with different number of tiles
        self.r4 = Row()
        self.r4.from_abbreviation("rrb")
        # Another empty row
        self.r5 = Row()

    def test_1_str(self):
        self.assertEqual(str(self.r0), "")
        self.assertEqual(str(self.r1), "rrbb")
        self.assertEqual(str(self.r2), "rrbb")
        self.assertEqual(str(self.r3), "rbbr")
        self.assertEqual(str(self.r4), "rrb")

    def test_2_eq(self):
        self.assertEqual(self.r1, self.r2)
        self.assertEqual(self.r0, self.r5)

    def test_3_neq(self):
        self.assertNotEqual(self.r0, self.r1)
        self.assertNotEqual(self.r1, self.r0)
        self.assertNotEqual(self.r1, self.r3)
        self.assertNotEqual(self.r3, self.r4)
        self.assertNotEqual(self.r4, self.r3)


if __name__ == "__main__":
    unittest.main()

