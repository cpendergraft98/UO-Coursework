"""
CIS 315 Homework 2

Author: Cole Pendergraft

Desc: Pulls the text format of a D.A.G. from stdin and creates an adjacency
matrix. The adjacency matrix is then used to compute the total number of
paths in the D.A.G., as well as the length of the shortest and longest paths
which are all output to stdout. There is a maximum complexity of O(n^2).
"""

import sys

# Creates an adjacency matrix given a list of edges and the number of nodes
def create_adj_matrix(edgelist, numnodes):
    # Initialize an empty matrix
    matrix = []
    # We want a numnodes*numnodes sized matrix, so we range from 0 to numnodes.
    for i in range(numnodes):
        # Initialize row i as being full of zeros
        row = [0]*numnodes
        # Iterate through the whole edge list
        for j in edgelist:
            # If the first element in the edge pair (j[0]-1) is equivalent to i
            if j[0]-1 == i:
                # Then we have an edge between i and j, so we navigate to the
                # j[1]-1 position in our matrix row and convert that value to 1
                row[j[1]-1] = 1
        # Add the row to the matrix
        matrix.append(row)
    return matrix

# Function to compute the total number of paths in the DAG. Takes the adjacency
# matrix and the number of nodes as arguments.
def numpaths(matrix, numnodes):
    # Initialize a list of length numnodes+1 full of zeros to be filled with
    # our paths
    paths = [0]*(numnodes + 1)
    # Set element 1 in the paths list to 1
    paths[1] = 1

    # Iterate through all of our nodes starting at 1
    for i in range(1, numnodes):
        # Get the row associated with said node. In the case of node 1 the
        # associated row is row 0.
        row = matrix[i-1]

        # Iterate through all of the nodes again
        for j in range(1, numnodes):
            # If row[j] = 1, then nodes i (row number) and j (column number)
            # have an edge between them
            if row[j] == 1:
                # Add the value at paths[i] to its neighbor in the list
                paths[j+1] += paths[i]

    # The final paths list should store the number of paths as the final element
    return paths[numnodes]

# Helper fucntion to aid with finding the shortest path. Finds the vertex with
# the minmum distance value from the vertices not in the shortest path tree.
# Takes the list of distances, the shortest path tree, and the number of nodes
# as arguments.
def minDistance(dist, spt, numnodes):
    # Initialize min as sys.maxsize as a temporary value
    min = sys.maxsize

    # For loop scans the elements not in the shortest path tree and returns
    # the shortest
    for i in range(numnodes):
        # Makes sure our element is smaller than the current min and is not
        # in the shortest path tree
        if dist[i] <= min and spt[i] == False:
            min = dist[i]
            position = i
    return position

# Finds the shortest path from 1 to numnodes. Takes the adjacency matrix, start
# value, and numnodes as arguments. Uses a modified Dijkstra's algorithm.
def find_shortest_path(matrix, start, numnodes):
    # Initialize a list of distances set to their maximum that is numnodes long.
    dist = [sys.maxsize] * numnodes
    # Set the distance for our start node to be 0
    dist[start] = 0
    # Track our visted nodes using a shortest path tree with every element
    # initially set to False
    spt = [False] * numnodes

    # Iterate through all the nodes
    for i in range(numnodes):
        # Use helper function to find the min distance vertex from those
        # not yet visited
        u = minDistance(dist, spt, numnodes)

        # Put that min distance vertex into the shortest path tree by updating
        # it to true.
        spt[u] = True

        # Iterate through all the nodes again
        for j in range(numnodes):
            # We only update the dist value of the adj nodes of the picked node
            # if our current dist > new dist and the node is not in the
            # shortest path tree
            if(matrix[u][j] > 0 and spt[j] == False and dist[j] > dist[u] + matrix[u][j]):
                # Updates the distance value of the adj nodes
                dist[j] = dist[u] + matrix[u][j]

    # Returns the shortest path
    return dist[j]

# Function to find the longest path of the DAG from 1 to numnodes. Takes the adj
# matrix, the start node, and the numnodes as arguments.
def find_longest_path(matrix, start, numnodes):
        # Initialize a list of distances set to 0 that is numnodes + 1 long
        dist = [0]*(numnodes + 1)

        # Iterate through the nodes
        for i in range(1, numnodes+1):
            # Grab the matrix row that corresponds with i
            row = matrix[i - 1]

            # Iterate through the subsequent nodes after 1
            for j in range(i+1, numnodes+1):
                # If the value at position i in the matrix row is 1 then there
                # is an edge between our nodes.
                if row[i] == 1:
                    # Update the distance value at node j to be the either
                    # dist[j] or dist[i], whatever is larger
                    dist[j] = max(dist[j], dist[i] + 1)

        # The largest value in the dist list will be the longest path.
        return max(dist)


def main():
    # Get the number of nodes and edges from stdin
    nodes = int(sys.stdin.readline())
    edges = int(sys.stdin.readline())

    # Create an array of edge pairings. This array will be used in the creation
    # of the adj matrix.
    edgelist = []
    for j in range(0, edges):
        # Read lines from stdin separated by whitespace
        edge = sys.stdin.readline().split(' ')
        # Map that edge to list
        edge = list(map(int, edge))
        # Append that list to our edge array
        edgelist.append(edge)

    # Create our adj matrix
    matrix = create_adj_matrix(edgelist, nodes)

    # Find the number of paths in our DAG
    count = numpaths(matrix, nodes)
    print("Total number of paths:", count)

    # Find the length of the shortest path in our DAG
    short = find_shortest_path(matrix, 1, nodes)
    print("Length of shortest path:", short)

    # Find the length of the longest path in our DAG
    long = find_longest_path(matrix, 1, nodes)
    print("Length of longest path:", long)

main()
