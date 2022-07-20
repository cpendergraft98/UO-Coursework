"""Test suite for problem Q1, Tree Height"""

import unittest
from q1_tree_height import *

class Test_Trees(unittest.TestCase):

    def test_1_it_was_just_laying_there(self):
        """Just a tomato laying on the ground"""
        magic_tomato = Fruit("tomato")
        self.assertEqual(magic_tomato.min_height(), 0)

    def test_2_short_bushy(self):
        """Tiniest tomato tree with a stem and two tomatoes"""
        tiny_bush = Branch(Fruit("tomato"), Fruit("tomato"))
        self.assertEqual(tiny_bush.min_height(), 1)

    def test_3_skew_left(self):
        """Longer on the left"""
        tree = Branch(Branch(Branch(Fruit("tomato"), Fruit("tomato")),
                             Fruit("tomato")), Fruit("tomato"))
        self.assertEqual(tree.min_height(), 1)

    def test_4_skew_right(self):
        """Enough to make a nice pot of spaghetti"""
        tree = Branch(Branch(Fruit("tomato"), Fruit("tomato")),
                      Branch(Branch(Branch(Fruit("tomato"), Fruit("tomato")),
                                    Branch(Fruit("tomato"), Fruit("tomato"))),
                             Branch(Branch(Fruit("tomato"), Fruit("tomato")),
                                    Fruit("tomato"))))
        self.assertEqual(tree.min_height(), 2)

if __name__ == "__main__":
    unittest.main()
