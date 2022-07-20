# multiAgents.py
# --------------
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


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [ index for index in range(len(scores)) if scores[index] == bestScore ]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        ''' avoid the ghost at all costs '''
        if newPos in [ghost.getPosition() for ghost in newGhostStates]:
            return -1000000
        ''' prevents pacman from getting stuck in a corner '''
        if action == 'Stop':
            return -1000000

        ''' get the closest distance to a ghost using the / -2 sets the ghost
        distance to be a lower priority to pacman, or at least visually a lower
        priority, while creating a reciprocal '''
        ghostdist = min([manhattanDistance(newPos, ghost.getPosition()) / -2 for ghost in newGhostStates])

        ''' get the furthest distance to a food pellet using the / -1 sets the
        food pellet distance to be a higher priority to pacman, or at least
        visually a higher priority, while creating a reciprocal '''
        currentFood = currentGameState.getFood().asList() ## creates a list of the current food pellets
        foodDist = max([manhattanDistance(newPos, i) / -1 for i in currentFood])

        return foodDist + ghostdist

def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        def minimax(gameState, depth):
            agents = gameState.getNumAgents()
            ghost = depth % agents
            legalActions = gameState.getLegalActions(ghost)
            max_depth = self.depth * agents

            ## based on class slides: define positive and negative infinity
            infinity = float("inf")
            neg_infinity = -float("inf")

            ## check if the game is over or depth equals max_depth
            if gameState.isWin() or gameState.isLose():
                return [None, self.evaluationFunction(gameState)]
            if depth == max_depth:
                return [None, self.evaluationFunction(gameState)]
            ## Pacman's max functionallity
            if depth % agents == 0:
                value = [None, neg_infinity]
                for action in legalActions:
                    nextMove = minimax(gameState.generateSuccessor(0, action), depth + 1)
                    if nextMove[1] > value[1]:
                        value = [action, nextMove[1]]
                return value
            ## Ghosts' min functionallity
            else:
                value = [None, infinity]
                for action in legalActions:
                    nextMove = minimax(gameState.generateSuccessor(ghost, action), depth + 1)
                    if nextMove[1] < value[1]:
                        value = [action, nextMove[1]]
                return value

        return minimax(gameState, 0)[0]

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        ''' based on class slides: define positive and negative infinity '''
        infinity = float("inf")
        neg_infinity = -float("inf")

        def alphaBetaPruning(gameState, depth, alpha, beta):
            ''' i would love to find a way to do this in getAction() instead
            but it aint working yet and im tired so gg 471 you win this round bbut ill be back '''
            agents = gameState.getNumAgents()
            ghost = depth % agents
            legalActions = gameState.getLegalActions(ghost)
            max_depth = self.depth * agents

            ''' check if the game is over '''
            if gameState.isWin() or gameState.isLose():
                return [None, self.evaluationFunction(gameState)]
            ''' check if depth equals max_depth '''
            if depth == max_depth:
                return [None, self.evaluationFunction(gameState)]
            ## Pacman's max functionallity
            if depth % agents == 0:
                value = [None, neg_infinity]
                for action in legalActions:
                    nextMove = alphaBetaPruning(gameState.generateSuccessor(0, action), depth + 1, alpha, beta)
                    alpha = max(nextMove[1], alpha)
                    if nextMove[1] > value[1]:
                        value = [action, nextMove[1]]
                    ## pruning logic
                    if alpha > beta:
                        break
                return value
            ## Ghosts' min functionallity
            else:
                value = [None, infinity]
                for action in legalActions:
                    nextMove = alphaBetaPruning(gameState.generateSuccessor(ghost, action), depth + 1, alpha, beta)
                    beta = min(nextMove[1], beta)
                    if nextMove[1] < value[1]:
                        value = [action, nextMove[1]]
                    ## pruning logic
                    if beta < alpha:
                        break
                return value

        return alphaBetaPruning(gameState, 0, neg_infinity, infinity)[0]


class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        def expectimax(gameState, depth):
            ''' i would love to find a way to do this in getAction() instead
            but it aint working yet and im tired so gg 471 you win this round bbut ill be back '''
            agents = gameState.getNumAgents()
            ghost = depth % agents
            legalActions = gameState.getLegalActions(ghost)
            max_depth = self.depth * agents

            ''' based on class slides: define positive and negative infinity '''
            neg_infinity = -float("inf")

            ''' check if the game is over '''
            if gameState.isWin() or gameState.isLose():
                return [None, self.evaluationFunction(gameState)]
            ''' check if depth equals max_depth '''
            if depth == max_depth:
                return [None, self.evaluationFunction(gameState)]
            ## if looking at pacman
            if depth % agents == 0:
                value = [None, neg_infinity]
                for action in legalActions:
                    nextMove = expectimax(gameState.generateSuccessor(0, action), depth + 1)
                    if nextMove[1] > value[1]:
                        value = [action, nextMove[1]]
                return value
            ## if looking at a ghost agent
            else:
                value = [None, 0]
                for action in legalActions:
                    nextMove = expectimax(gameState.generateSuccessor(ghost, action), depth + 1)
                    value[0] = action
                    value[1] += nextMove[1]
                return value

        return expectimax(gameState, 0)[0]


def betterEvaluationFunction(currentGameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    """

    '''pacmanState = currentGameState.getPacmanState()
    pacmanPosition = currentGameState.getPacmanPosition()
    ghostStates = currentGameState.getGhostStates()

    print(pacmanState)

    print(pacmanPosition)

    print(ghostStates)'''
    # Useful information you can extract from a GameState (pacman.py)
    pos = currentGameState.getPacmanPosition()
    currentFood = currentGameState.getFood().asList() ## creates a list of the current food pellets
    ghostStates = currentGameState.getGhostStates()
    scaredTimes = [ghostState.scaredTimer for ghostState in ghostStates]

    caps = currentGameState.getCapsules()
    ##walls = currentGameState.getWalls() ''' unused '''

    "*** YOUR CODE HERE ***"
    neg_infinity = -float("inf")
    ''' avoid the ghost at all costs '''
    if pos in [ghost.getPosition() for ghost in ghostStates]:
        return neg_infinity

    ''' logic for eating capsules and hunting the ghost '''
    if len(caps) != 0:
        if scaredTimes != 0:
            ''' get the closest distance to a ghost '''
            ## -2 was pulled from the evaluation function at the beging of the project
            ghostDist = min([manhattanDistance(pos, ghost.getPosition()) / -2 for ghost in ghostStates])
            return currentGameState.getScore() + ghostDist
        else:
            ## using -10 was an arbitrary number that produced the best avg score
            capDist = min([manhattanDistance(pos, cap) / -10 for cap in caps])
            return currentGameState.getScore() + capDist

    ''' get the closest distance to a ghost '''
    if ghostStates:
        ## -2 was pulled from the evaluation function at the beging of the project
        ghostDist = min([manhattanDistance(pos, ghost.getPosition()) / -2 for ghost in ghostStates])
    ## does not seem to improve the testing but added to match the food distance logic
    else:
        ghostDist = 0

    ''' get the furthest distance to a food pellet '''
    if currentFood:
        ## using -10 was an arbitrary number that produced the best avg score
        foodDist = max([manhattanDistance(pos, i) / -10 for i in currentFood])
    ## without this else statement "pacman crashes"
    else:
        foodDist = 0

    ''' without the currentGameState.getScore() pacman is less efficent '''
    return currentGameState.getScore() + foodDist + ghostDist


# Abbreviation
better = betterEvaluationFunction
