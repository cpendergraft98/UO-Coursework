# valueIterationAgents.py
# -----------------------
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


# valueIterationAgents.py
# -----------------------
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


import mdp, util

from learningAgents import ValueEstimationAgent
import collections

class ValueIterationAgent(ValueEstimationAgent):
    """
        * Please read learningAgents.py before reading this.*

        A ValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs value iteration
        for a given number of iterations using the supplied
        discount factor.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 100):
        """
          Your value iteration agent should take an mdp on
          construction, run the indicated number of iterations
          and then act according to the resulting policy.

          Some useful mdp methods you will use:
              mdp.getStates()
              mdp.getPossibleActions(state)
              mdp.getTransitionStatesAndProbs(state, action)
              mdp.getReward(state, action, nextState)
              mdp.isTerminal(state)
        """
        self.mdp = mdp
        self.discount = discount
        self.iterations = iterations
        self.values = util.Counter() # A Counter is a dict with default 0
        self.runValueIteration()

    def runValueIteration(self):
        # Write value iteration code here
        "*** YOUR CODE HERE ***"
        ## declaration of a value thats always smaller than another
        neg_infinity = -float("inf")
        ## runs value iteration for the specified number of iterations before the constructor returns
        for i in range(self.iterations):
            dic = util.Counter()
            ## looking at all possible states within the board
            for state in self.mdp.getStates():
                ## check if the state is not a TERMINAL_STATE
                if(not self.mdp.isTerminal(state)):
                    ## set the max value to start as imposible small
                    max_val = neg_infinity
                    ## look at all possible states (k+1) when at state k
                    for action in self.mdp.getPossibleActions(state):
                        Qvalue = self.getQValue(state, action)
                        max_val = max([max_val, Qvalue])
                    dic[state] = max_val
            self.values = dic

    def getValue(self, state):
        """
          Return the value of the state (computed in __init__).
        """
        return self.values[state]


    def computeQValueFromValues(self, state, action):
        """
          Compute the Q-value of action in state from the
          value function stored in self.values.
        """
        "*** YOUR CODE HERE ***"
        ##util.raiseNotDefined()
        Q = 0
        for state_prime, prob in self.mdp.getTransitionStatesAndProbs(state, action):
            reward = self.mdp.getReward(state, action, state_prime)
            ## function provided in lecture 10 slide 25, and project part1 spec
            Q += prob * (reward + (self.discount * self.values[state_prime]))
        return Q

    def computeActionFromValues(self, state):
        """
          The policy is the best action in the given state
          according to the values currently stored in self.values.

          You may break ties any way you see fit.  Note that if
          there are no legal actions, which is the case at the
          terminal state, you should return None.
        """
        "*** YOUR CODE HERE ***"
        ##util.raiseNotDefined()
        ## declaration of a value thats always smaller than another
        neg_infinity = -float("inf")
        ## initially no action taken
        a_taken = None
        ## initially set max_val to be impossibly low
        max_val = neg_infinity
        ## for all legal actions from a current state
        for action in self.mdp.getPossibleActions(state):
            ## get the value of an action
            Q = self.getQValue(state, action)
            ## if the action is more profitable use that action instead
            if Q > max_val:
                a_taken = action
                max_val = Q
        return a_taken

    def getPolicy(self, state):
        return self.computeActionFromValues(state)

    def getAction(self, state):
        "Returns the policy at the state (no exploration)."
        return self.computeActionFromValues(state)

    def getQValue(self, state, action):
        return self.computeQValueFromValues(state, action)

class AsynchronousValueIterationAgent(ValueIterationAgent):
    """
        * Please read learningAgents.py before reading this.*

        An AsynchronousValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs cyclic value iteration
        for a given number of iterations using the supplied
        discount factor.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 1000):
        """
          Your cyclic value iteration agent should take an mdp on
          construction, run the indicated number of iterations,
          and then act according to the resulting policy. Each iteration
          updates the value of only one state, which cycles through
          the states list. If the chosen state is terminal, nothing
          happens in that iteration.

          Some useful mdp methods you will use:
              mdp.getStates()
              mdp.getPossibleActions(state)
              mdp.getTransitionStatesAndProbs(state, action)
              mdp.getReward(state)
              mdp.isTerminal(state)
        """
        ValueIterationAgent.__init__(self, mdp, discount, iterations)

    def runValueIteration(self):
        "*** YOUR CODE HERE ***"
        ## retreve the states
        all_states = self.mdp.getStates()
        for i in range(self.iterations):
            indede = i % len(all_states)
            current_state = all_states[indede]
            ## check for terminal state
            if(self.mdp.isTerminal(current_state)):
                continue
            ## if not terminal calculate new value for the state
            legal_actions = self.mdp.getPossibleActions(current_state)
            list = []
            for action in legal_actions:
                list.append(self.computeQValueFromValues(current_state, action))
            new_value = max(list)
            self.values[current_state] = new_value

class PrioritizedSweepingValueIterationAgent(AsynchronousValueIterationAgent):
    """
        * Please read learningAgents.py before reading this.*

        A PrioritizedSweepingValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs prioritized sweeping value iteration
        for a given number of iterations using the supplied parameters.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 100, theta = 1e-5):
        """
          Your prioritized sweeping value iteration agent should take an mdp on
          construction, run the indicated number of iterations,
          and then act according to the resulting policy.
        """
        self.theta = theta
        ValueIterationAgent.__init__(self, mdp, discount, iterations)

    def getPredecessors(self):
        ## Gets predecessors for the sweeping value iteration agent
        predecessors = {}

        ## iterate through all states
        for s in self.mdp.getStates():

            ## ensure that the state is not terminal
            if not self.mdp.isTerminal(s):

                ## iterate through all actions available to the given state
                for action in self.mdp.getPossibleActions(s):

                    ## iterate through the new states and probabilites generated by
                    ## getTransitionStatesAndProbs
                    for new_state, i in self.mdp.getTransitionStatesAndProbs(s, action):

                        ## If the new state is in our list of predecessors
                        if new_state in predecessors:
                            ## add the state to the predecessors dict at the new_state
                            ## position to signify new_state is a predecessor to s
                            predecessors[new_state].add(s)

                        else:

                            # Otherwise we add a new dictionary based around the state
                            # at position new_state to signify new_state is a predecessor
                            # of s
                            predecessors[new_state] = {s}

        return predecessors

    def runValueIteration(self):
        "*** YOUR CODE HERE ***"

        ## Get predecessors of all states
        preds = self.getPredecessors()

        ## Initialize an empty priority queue.
        pQueue = util.PriorityQueue()

        # Generate list of states
        all_states = self.mdp.getStates()

        # Iterate through all states
        for s in all_states:
            # Make sure s is a non-terminal state
            if not self.mdp.isTerminal(s):

                # Iterate through list of actions and compute Q value for taking
                # action from current state, keep only the max q value.
                list = []
                for a in self.mdp.getPossibleActions(s):
                    list.append(self.computeQValueFromValues(s, a))
                maxQ = max(list)

                # Find abs value of self.values[s] - Max Q value
                diff = abs(maxQ - self.values[s])

                # Push state into prio queue with -diff as priority
                pQueue.update(s, -diff)

        ##For iteration in 0, 1, 2, ..., self.iterations - 1
        for i in range(self.iterations):
            ## If prio queue is empty, then we terminate
            if pQueue.isEmpty():
                break

            ## pop state from prio queue
            s = pQueue.pop()

            ## ensure the state is non terminal
            if not self.mdp.isTerminal(s):

                # initialize an empty list
                list = []

                ## iterate through available actions from state
                for a in self.mdp.getPossibleActions(s):
                    # Add q values to the list
                    list.append(self.computeQValueFromValues(s, a))

                ## take the max q value out of the list and set it to the value
                ## of the state
                maxQ = max(list)
                self.values[s] = maxQ

                ## iterate through all predecessors of the state
                for p in preds[s]:

                    ## ensure that the predecessor is non terminal
                    if not self.mdp.isTerminal(p):
                        # initialize an empty list
                        list = []
                        # iterate through all actinos available from the predecessor
                        for a in self.mdp.getPossibleActions(p):
                            # add q values of p to the list
                            list.append(self.computeQValueFromValues(p, a))
                        # take the max value out of the list
                        maxQ = max(list)

                        # compute diff as the absolute value of the maximum q value minus the current
                        # value at p
                        diff = abs(maxQ - self.values[p])

                        ## if diff is greater than our current theta, we update the value of p
                        ## in the prio queue
                        if diff > self.theta:
                            pQueue.update(p, -diff)
