"""
CIS 315 Homework 5

Author: Cole Pendergraft
"""

import sys
import math

# Helper function to read input from the command line
def readinput():

    # Get the first line containing n and m
    temp = sys.stdin.readline()
    # Split line at whitespace
    temp = temp.split()

    # n = number of coins
    numcoins = int(temp[0])
    # m = number of targets
    numtargets = int(temp[1])

    # Store a list of the denominations
    denoms = []
    for i in range(numcoins):
        val = int(sys.stdin.readline())
        # We want 5 copies of each coin
        denoms.extend([val] * 5)

    # Store a list of the values to be tested
    targets = []
    for i in range(numtargets):
        val = int(sys.stdin.readline())
        targets.append(val)

    return denoms, targets

# Function to execute the MaxZondorCoin algorithm
def MaxZondorCoin(denoms, target):

    # Create the memory array
    K = [[0 for x in range(target + 1)] for x in range(len(denoms) + 1)]

    for i in range(len(denoms) + 1):

        for t in range(target + 1):

            # If k = 0 and t > 0 base case
            if t > 0 and i == 0:
                K[i][t] = -math.inf

            # If t = 0 base case
            elif i == 0 or t == 0:
                K[i][t] = 0

            # Make sure that the denomiation is less than target value
            elif denoms[i - 1] <= t:
                # If it is and we don't hit the other base cases, then we perform
                # our recurrence calculation
                K[i][t] = max(1 + K[i-1][t - denoms[i-1]], K[i-1][t])

            else:
                # If it isn't, we set K[i][t] equal to its left neighbor
                K[i][t] = K[i - 1][t]

    # Return the value at position [n][t] to find our maxCoin for the target
    return K[len(denoms)][t]

def main():

    # Get necessary values from stdin
    denoms, targets = readinput()

    # Run the MaxZondorCoin function
    for target in targets:

        # If our target is negative we can't do anything
        if target < 0:
            print(f"target: {target}, not possible")

        else:
            # Call the maxCoin function on
            maxCoin = MaxZondorCoin(denoms, target)

            # If maxCoin is -inf then the target is impossible to reach
            if (maxCoin == -math.inf):
                statement = "not possible"

            # Handles printing of correct outputsSS
            else:
                statement = f"max coins: {maxCoin}"

            print(f"target: {target}, {statement}")


main()
