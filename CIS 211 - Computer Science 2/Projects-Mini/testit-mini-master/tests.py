"""Unit tests for testme.py

CIS 211 Mini Project 2
Author: Cole Pendergraft"""

import unittest
from buggy import *

class TestMaxRun(unittest.TestCase):

    def test_max_run_example(self):
        self.assertEqual(max_run([1, 2, 2, 2, 3]), [2, 2, 2])
        self.assertEqual(max_run(["m", "m", "m", "n", "n"]), ["m", "m", "m"])#Works fine

        self.assertEqual(max_run([1, 2, 2, 3, 3, 3, 3]), [3, 3, 3, 3]) #First bug found, fails if longest run is at the
                                                                       #end of the list.

        self.assertEqual(max_run([]), []) #Second bug found, the code fails if an empty list is passed as an argument.
if __name__ == "__main__":
    unittest.main()

