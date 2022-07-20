"""Test suite for Q2, bit manipulation"""
import unittest
from typing import Tuple
from q2_bits import *

class Test_Packing(unittest.TestCase):

    def test_1_layout(self):
        w = pack556(31, 0, 0)
        self.assertEqual(w, 0b11111_00000_000000)
        v = pack556(0, 31, 0)
        self.assertEqual(v, 0b00000_11111_000000)
        u = pack556(0, 0, 63)
        self.assertEqual(u, 0b00000_00000_111111)

    def test_2_extract(self):
        w = pack556(19, 21, 33)
        x,y,z = unpack556(w)
        self.assertEqual(x, 19)
        self.assertEqual(y, 21)
        self.assertEqual(z, 33)

    def test_3_all_one(self):
        w = pack556(31,31,63)
        x,y,z = unpack556(w)
        self.assertEqual((x,y,z), (31, 31, 63))

    def test_4_high_bits(self):
        w = pack556(0b10000, 0b10000, 0b100000)
        x,y,z = unpack556(w)
        self.assertEqual((x,y,z), (0b10000, 0b10000, 0b100000))

if __name__ == "__main__":
    unittest.main()
