"""
The game state and logic (model component) of 512, 
a game based on 2048 with a few changes. 
This is the 'model' part of the model-view-controller
construction plan.  It must NOT depend on any
particular view component, but it produces event 
notifications to trigger view updates.

Extra credit: implemented 2048 scoring. 512 scoring is default, but can be changed on line 252 with game=2048
"""

from game_element import GameElement, GameEvent, EventKind
from typing import List, Tuple, Optional
import random

# Configuration constants
GRID_SIZE = 4

class Vec():
    """A Vec is an (x,y) or (row, column) pair that
    represents distance along two orthogonal axes.
    Interpreted as a position, a Vec represents
    distance from (0,0).  Interpreted as movement,
    it represents distance from another position.
    Thus we can add two Vecs to get a Vec.
    """
    #Fixme:  We need a constructor, and __add__ method, and __eq__.
    def __init__(self, x: int, y: int):
        """x represents the row coordinate, i.e. vertical with 0 at the top, positive down
        y represents the column coordinate, i.e. horizontal with positive right"""
        self.x = x
        self.y = y

    def __eq__(self, other):
        """Determines if two Vec objects have the same row and column."""
        return self.x == other.x and self.y == other.y

    def __add__(self, other: "Vec") -> "Vec":
        "Vecs can be added by summing like components, so adding is delegated to int __add__"
        return Vec(self.x + other.x, self.y + other.y)


class Tile(GameElement):
    """A slidy numbered thing."""
    def __init__(self, pos: Vec, value: int):
        super().__init__()
        self.row = pos.x
        self.col = pos.y
        self.value = value

    def __repr__(self):
        """Not like constructor --- more useful for debugging"""
        return f"Tile[{self.row},{self.col}]:{self.value}"

    def __str__(self):
        return str(self.value)

    def move_to(self, new_pos: Vec):
        self.row = new_pos.x
        self.col = new_pos.y
        self.notify_all(GameEvent(EventKind.tile_updated, self))

    def __eq__(self, other: "Tile"):
        if isinstance(other, Tile):
            return self.value == other.value
        else:
            return self.value is other

    def merge(self, other: "Tile"):
        # This tile incorporates the value of the other tile
        self.value = self.value + other.value
        self.notify_all(GameEvent(EventKind.tile_updated, self))
        # The other tile has been absorbed.  Resistance was futile.
        other.notify_all(GameEvent(EventKind.tile_removed, other))


class Board(GameElement):
    """The game grid.  Inherits 'add_listener' and 'notify_all'
    methods from game_element.GameElement so that the game
    can be displayed graphically.
    """
    def __init__(self, rows=4, cols=4):
        super().__init__()
        self.rows = rows
        self.cols = cols
        self.tiles = [ ]
        self.totalScore = 0
        for row in range(rows):
            row_tiles = [ ]
            for col in range(cols):
                row_tiles.append(None)
            self.tiles.append(row_tiles)

    def __getitem__(self, pos: Vec) -> Tile:
        return self.tiles[pos.x][pos.y]

    def __setitem__(self, pos: Vec, tile: Tile):
        self.tiles[pos.x][pos.y] = tile

    def _empty_positions(self) -> List[Vec]:
        """Return a list of positions of None values,
        i.e., unoccupied spaces.
        """
        empties = []
        for row in range(len(self.tiles)):
            for col in range(len(self.tiles[row])):
                if self[Vec(row, col)] == None:
                    empties.append(Vec(row, col))
        return empties

    def has_empty(self) -> bool:
        """Is there at least one grid element without a tile?"""
        if len(self._empty_positions()) > 0:
            return True
        else:
            return False

    def place_tile(self, value=None):
        """Place a tile on a randomly chosen empty square."""
        empties = self._empty_positions()
        assert len(empties) > 0
        choice = random.choice(empties)
        row, col = choice.x, choice.y
        if value is None:
            # 0.1 probability of 4
            if random.random() < 0.1:
                value = 4
            else:
                value = 2
        new_tile = Tile(Vec(row, col), value)
        self.tiles[row][col] = new_tile
        self.notify_all(GameEvent(EventKind.tile_created, new_tile))

    def to_list(self) -> List[List[int]]:
        """Test scaffolding: represent each Tile by its
        integer value and empty positions as 0
        """
        result = [ ]
        for row in self.tiles:
            row_values = []
            for col in row:
                if col is None:
                    row_values.append(0)
                else:
                    row_values.append(col.value)
            result.append(row_values)
        return result

    def from_list(self, values: List[List[int]]):
        """Test scaffolding: set board tiles to the
        given values, where 0 represents an empty space.
        """
        for row in range(len(values)):
            for col in range(len(values[row])):
                if values[row][col] != 0:
                    new_tile = Tile(Vec(row, col), values[row][col])
                    self.tiles[row][col] = new_tile
                    self.notify_all(GameEvent(EventKind.tile_created, new_tile))

    def in_bounds(self, pos: Vec) -> bool:
        """Is position (pos.x, pos.y) a legal position on the board?"""
        rowCondition = ((self.rows - 1) >= pos.x) and (pos.x >= 0)
        colCondition = ((self.cols - 1) >= pos.y) and (pos.y >= 0)
        return rowCondition and colCondition

    def slide(self, pos: Vec,  dir: Vec):
        """Slide tile at row,col (if any)
        in direction (dx,dy) until it bumps into
        another tile or the edge of the board.
        """
        if self[pos] is None:
            return
        while True:
            new_pos = pos + dir
            if not self.in_bounds(new_pos):
                break
            if self[new_pos] is None:
                self._move_tile(pos, new_pos)
            elif self[pos] == self[new_pos]:
                self.totalScore += self[pos].value # if there is a merge, store this value to keep 2048 count
                self[pos].merge(self[new_pos])
                self._move_tile(pos, new_pos)
                break  # Stop moving when we merge with another tile
            else:
                # Stuck against another tile
                break
            pos = new_pos

    def _move_tile(self, old_pos: Vec, new_pos: Vec):
        """Copys a tile object from an old position, old_pos to a new position, new_pos,
        then sets the old position to None and moves the Tile via move_to Tile method. """
        oldTile = self.tiles[old_pos.x][old_pos.y]
        self.tiles[new_pos.x][new_pos.y] = oldTile
        self.tiles[old_pos.x][old_pos.y] = None
        oldTile.move_to(new_pos)

    def left(self, dx=0, dy=-1):
        """Moves all tiles on the board to the left"""
        # start by sliding the last tile in the row in the direction you are moving tiles and work backward per game \
        # rules
        # original implementation
        # for row in range(len(self.tiles)):
        #     for col in range(len(self.tiles[row])):
        #         self.slide(Vec(row, col), Vec(dx, dy))
        # ._move implementation
        self._move(dx, dy)

    def up(self, dx=-1, dy=0):
        """Moves all tiles on the board up"""
        # start by sliding the last tile in the row in the direction you are moving tiles and work backward per game \
        # rules
        # original implementation
        # for row in range(len(self.tiles)):
        #     for col in range(len(self.tiles[row])):
        #         self.slide(Vec(row, col), Vec(dx, dy))
        # ._move implementation
        self._move(dx, dy)

    def right(self, dx=0, dy=1):
        """Moves all tiles on the board to the right"""
        # start by sliding the last tile in the row in the direction you are moving tiles and work backward per game \
        # rules
        # original implementation
        # for row in range(len(self.tiles)-1, -1, -1):
        #     for col in range(len(self.tiles[row])-1, -1, -1):
        #         self.slide(Vec(row, col), Vec(dx, dy))
        # ._move implementation
        self._move(dx, dy)

    def down(self, dx=1, dy=0):
        """Moves all tiles on the board down"""
        # start by sliding the last tile in the row in the direction you are moving tiles and work backward per game \
        # rules
        # original implementation
        # for row in range(len(self.tiles)-1, -1, -1):
        #     for col in range(len(self.tiles[row])-1, -1, -1):
        #         self.slide(Vec(row, col), Vec(dx, dy))
        # ._move implementation
        self._move(dx, dy)

    def _move(self, dx, dy):
        """generalized method to move left, right, up, and down"""
        # loop through rows and columns from left->right & top->bottom
        if (dx < 0) or (dy < 0): # for left and up
            for row in range(len(self.tiles)):
                for col in range(len(self.tiles[row])):
                    self.slide(Vec(row, col), Vec(dx, dy))

        else: # for right and down, reverse order right->left, bottom->top
            for row in range(len(self.tiles) - 1, -1, -1): # reversed range
                for col in range(len(self.tiles[row]) - 1, -1, -1): # reversed range
                    self.slide(Vec(row, col), Vec(dx, dy))

    def score(self, game=512) -> int:
        """Calculate a score from the board.
        (Differs from classic 1024, which calculates score
        based on sequence of moves rather than state of
        board.
        """
        # for 512
        if game == 512:
            result = 0
            for row in self.tiles:
                for col in row:
                    if col is None:
                        pass
                    else:
                        result += col.value
            return result

        elif game ==2048:
        # for extra credit 2048 scoring; I add to a count every time there is a merge (stored at self.totalScore),
        # considering that is when scoring occurs in 2048, then I return that count.
            return self.totalScore

