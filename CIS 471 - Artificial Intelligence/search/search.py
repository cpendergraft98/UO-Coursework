# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST

    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    """
    "*** YOUR CODE HERE ***"

    """
    Cole Pendergraft
    Colton Lobdell
    """

    # We comment very heavily, it's to help us in the future when we study these
    # assignments.

    # NOTE: We define a "node" as each tuple of (State, Direction, Cost)
    # elements. This will help in understanding future comments.

    # Instantiate the fringe which will be a stack in the case of DFS.
    fringe = util.Stack()

    # We expand our root node every time so we want to start with it in our
    # closed set. If the root node is the goal state then this closed set doesn't
    # play any role so it isn't an issue to add the root node to it right away.
    closed = [problem.getStartState()]

    # The start node does not naturally have an associated direction so we instead
    # pass it an empty list in that space. We will end up populating this empty
    # list with our path, and return it at the end to give pacman his directions.
    # We also need to assign it an arbitrary cost so that it fits the node
    # structure of (State, Direction, Cost) even though this cost will have no
    # impact on the final path.
    fringe.push((problem.getStartState(), [], 1))

    while not fringe.isEmpty():

        # As we said, we don't ever use the cost variable when we are doing DFS, but
        # it is still pushed into the fringe as an element of each node object
        # so we need to dequeue it along with the direction and the state or our
        # fringe will be full of unneeded cost values.
        # The directions variable is an empty list on our first iteration, but
        # every subsequent iteration sees a new direction added to it until it
        # reaches a goal and is returned as pacman's path.
        state, directions, cost = fringe.pop()

        # We must always check if our current state is the goal state. If this
        # statement is triggered on our first iteration (i.e. the root is the
        # goal) then we end up just returning an empty list of directions.
        if problem.isGoalState(state):
            return directions

        # getSuccessors returns a list of successor node objects, and we look
        # at each of the three elements of the node object to decide what
        # to do next.
        for successor, direction, cost in problem.getSuccessors(state):
            if successor not in closed:
                # If our successor node has not been added to our closed set
                # then we do that now.
                closed.append(successor)

                # We push the successor onto the stack, as well as add its
                # relevant direction element into our directions list, which we
                # then push back onto the stack. The directions list is
                # constantly removed from the fringe, appended, and then pushed
                # back onto the fringe to be removed again for the next node.
                fringe.push((successor, directions + [direction], cost))

    print("Your fringe is empty and that is very bad")
    return []


def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"

    # Other than using a Queue for the fringe, everything about the BFS
    # implementation is identical to the implementation for DFS.
    fringe = util.Queue()

    closed = [problem.getStartState()]

    fringe.push((problem.getStartState(), [], 1))

    while not fringe.isEmpty():

        state, directions, cost = fringe.pop()

        if problem.isGoalState(state):
            return directions

        for successor, direction, cost in problem.getSuccessors(state):

            if successor not in closed:
                closed.append(successor)
                fringe.push((successor, directions + [direction], cost))


    print("Your fringe is empty and that is very bad")
    return []

def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"

    # Initialize the fringe as a PriorityQueue with UCS.
    fringe = util.PriorityQueue()

    closed = [problem.getStartState()]

    # Costs are now important to our overall pathing, so now we don't want to
    # use some arbitrary cost for the root node, but instead use a cost of 0
    # because it costs nothing to move to our start node. Tracking this cost
    # and using it to decide where to path is the only real difference between
    # UCS and BFS.
    fringe.push((problem.getStartState(), [], 0), 0)

    while not fringe.isEmpty():

        state, directions, cost = fringe.pop()

        if problem.isGoalState(state):
            return directions

        for successor, direction, cost in problem.getSuccessors(state):

            if successor not in closed:
                # As said, the big difference between UCS and BFS is that with UCS
                # we use the cost of traveling to a node as the priority value in a
                # priority queue, which helps pacman decide which direction to
                # go next. This is where we get the cost of going a specific direction:
                count = problem.getCostOfActions(directions)

                closed.append(successor)
                fringe.push((successor, directions + [direction], cost), count)

    print("Your fringe is empty and that is very bad")
    return []

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"

    fringe = util.PriorityQueue()

    closed = [problem.getStartState()]

    # Our start node should always cost 0 to move to, so we can initialize it as
    # we did in UCS.
    fringe.push((problem.getStartState(), [], 0), 0)

    while not fringe.isEmpty():

        state, directions, cost = fringe.pop()

        if problem.isGoalState(state):
            return directions

        for successor, direction, cost in problem.getSuccessors(state):

            if successor not in closed:
                # The major difference between UCS and A* is that with A* we
                # use the cost of moving to a node + some heuristic in order to
                # determine how pacman should path through the maze. In this case,
                # our heuristic is the manhattan distance from our current state
                # to the goal node.
                # When we make the call to run this code, we specify what
                # the "heuristic" function does. For example, if we want to use
                # the manhattanHeuristic as our heuristic value, when we run the
                # code we specify that heuristic = manhattanHeuristic, so setting
                # h = heuristic(successor, problem) is the equivalent of
                # h = manhattanHeuristic(successor, problem). We could specify
                # other heuristic functions as well.
                h = heuristic(successor, problem)

                count = problem.getCostOfActions(directions)

                total = h + count
                closed.append(successor)
                fringe.push((successor, directions + [direction], cost),  total)

# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
