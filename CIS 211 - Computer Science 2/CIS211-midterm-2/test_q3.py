import unittest
from q3_logic import *

# Weird spectrum just for testing
BWG = [Color.black, Color.white, Color.green]

class Test_1_Monochrome(unittest.TestCase):

    def test_1_full_bw(self):
        grid = Grid([[Color.black, Color.white, Color.black],
                     [Color.black, Color.white, Color.white]])
        self.assertTrue(grid.some_column_all_colors(BW))

        self.assertFalse(grid.some_column_all_colors(BWG))

    def test_2_not_in_column(self):
        grid = Grid([[Color.black, Color.white, Color.black],
                     [Color.black, Color.white, Color.black]])
        self.assertFalse(grid.some_column_all_colors(BW))

    def test_3_long_columns(self):
        grid = Grid([[Color.black, Color.white, Color.white],
                     [Color.black, Color.white, Color.white],
                     [Color.black, Color.white, Color.white],
                     [Color.black, Color.white, Color.white],
                     [Color.black, Color.white, Color.white],
                     [Color.black, Color.black, Color.white],
                     ])
        self.assertTrue(grid.some_column_all_colors(BW))
        self.assertFalse(grid.some_column_all_colors(BWG))


class Test_2_Rainbow(unittest.TestCase):
    def test_1_rainbow(self):
        # A grid with full rainbow of colors in third column
        grid = Grid(
            [[Color.red, Color.green, Color.red, Color.red]
            ,[Color.green, Color.red, Color.green, Color.green]
            ,[Color.blue, Color.orange, Color.blue, Color.orange]
            ,[Color.orange, Color.blue, Color.orange, Color.blue]
            ,[Color.indigo, Color.violet, Color.indigo, Color.violet]
            ,[Color.indigo, Color.yellow, Color.violet, Color.violet]
            ,[Color.blue,  Color.green, Color.yellow, Color.yellow]
            ,[Color.red, Color.green, Color.red, Color.red]])
        self.assertTrue(grid.some_column_all_colors(RAINBOW))
        self.assertFalse(grid.some_column_all_colors(BW))

    def test_2_rainbow(self):
        # No single column has all the rainbow colors
        grid = Grid([[Color.red, Color.green, Color.red, Color.red]
            ,[Color.green, Color.red, Color.green, Color.green]
            ,[Color.blue, Color.orange, Color.blue, Color.orange]
            ,[Color.orange, Color.blue, Color.orange, Color.blue]
            ,[Color.indigo, Color.violet, Color.indigo, Color.violet]
            ,[Color.indigo, Color.violet, Color.yellow, Color.violet]
            ,[Color.blue,  Color.green, Color.red, Color.yellow]
            ,[Color.red, Color.green, Color.yellow, Color.red]])
        self.assertFalse(grid.some_column_all_colors(RAINBOW))
        # But several columns have at least the primary colors
        self.assertTrue(grid.some_column_all_colors(PRIMARIES))

if __name__ == "__main__":
    unittest.main()