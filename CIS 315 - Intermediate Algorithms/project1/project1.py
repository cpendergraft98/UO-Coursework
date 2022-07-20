"""
CIS 315 Project 1

Author: Cole Pendergraft

Pulls "x y" pairs from stdin and returns a "x+y x*y" pair. Very specific input
structure:
First value pulled from stdin is the number of lines to be computed. Must be an
individual value. 
Subsequent stdin take the form "x y" without quotations. Lack of or extra
whitespace will cause a crash and extra or too few inputs will also cause a
crash.
"""
import sys

def main():
    # First value pulled from stdin is the number of subsequent lines
    numLines = int(sys.stdin.readline())

    # Perform operations on lines from stdin numLines times.
    for i in range(numLines):
        # Pull lines from stdin
        line = sys.stdin.readline()
        # Split input lines at whitespace
        xy = line.split(' ')
        # Grab the X element
        x = int(xy[0])
        # Grab the Y element
        y = int(xy[1])
        # Compute the sum
        sum = x+y
        # Compute the multiplication
        mult = x*y
        # Print "sum mult" pair to stdout according to project specs
        print(f"{sum} {mult}")

main()
