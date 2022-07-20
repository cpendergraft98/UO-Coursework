"""IntervalCollection (midterm problem, CIS 211)

AUTHOR: Cole Pendergraft"""

from typing import List

class Interval:
    """A closed interval of integers contains its end points"""
    def __init__(self, bound_low: int, bound_high: int):
        self.low = bound_low
        self.high = bound_high

    def __repr__(self) -> str:
        return f"Interval({self.low}, {self.high})"

    def __str__(self) -> str:
        return f"[{self.low}, {self.high}]"

    def contains(self, i: int) -> bool:
        if (i < self.low) or (i > self.high):
            return False
        else:
            return True


class IntervalCollection:
    """Wraps a list of closed intervals"""
    def __init__(self):
        self.items: List[Interval]  = [ ]

    def append(self, interval: Interval):
        """Add interval to the list of intervals"""
        self.items.append(interval)

    def contains(self, i: int) -> bool:
        """True if any interval contains i"""
        count = 0
        for x in self.items:
            if (i >= x.low) and (i <= x.high):
                count += 1
        return (count > 0)


