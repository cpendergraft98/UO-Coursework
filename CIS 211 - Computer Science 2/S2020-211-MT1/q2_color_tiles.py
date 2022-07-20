"""Rows of tiles (Midterm problem)

AUTHOR: Cole Pendergraft"""

import enum
from typing import List

class Color(enum.Enum):
    red = 1
    blue = 2

    def __str__(self) -> str:
        """'r' for red, 'b' for blue"""
        return self.name[0]

ABBREVIATIONS = { 'r': Color.red,
                  'b': Color.blue
                }


class Tile:
    """A single colored tile, either red or blue"""
    def __init__(self, tile_color: Color):
        self._color = tile_color

    def color(self) -> Color:
        return self._color

    def __eq__(self, other: "Tile"):
        """Tiles are equal if they have the same color"""
        return (self._color == other._color)

    def __str__(self) -> str:
        return str(self._color)


class Row:
    """A row of colored tiles"""
    def __init__(self):
        self.tiles = []

    def append(self, tile: Tile):
        self.tiles.append(tile)

    def __str__(self) -> str:
        new = ''
        for i in self.tiles:
            new += str(i)
        print(new)
        return f"{new}"# This is failing in a way that does not make any sense. Instead of returning when it gets to the
                    # return statement, it chooses to iterate through the list again, which is proven by the fact that
                    # the code print(new) will execute twice. Not sure what I can possibly do about this.

    def __eq__(self, other: "Row") -> bool:
        return self.tiles == other.tiles

    def from_abbreviation(self, abbrv: str):
        r = abbrv.split()
        for i in r:
            self.append(i)
        return self.tiles

def main():
    row = Row()
    row.append(Tile(Color.blue))
    row.append(Tile(Color.red))
    row.append(Tile(Color.blue))

    print(row)

    row2 = Row()
    row2.from_abbreviation("brb")
    assert row == row2

if __name__ == "__main__":
    main()
