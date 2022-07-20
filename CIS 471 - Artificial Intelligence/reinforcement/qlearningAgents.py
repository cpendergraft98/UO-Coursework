# qlearningAgents.py
# ------------------
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


from game import *
from learningAgents import ReinforcementAgent
from featureExtractors import *

import random,util,math

class QLearningAgent(ReinforcementAgent):
    """
      Q-Learning Agent

      Functions you should fill in:
        - computeValueFromQValues
        - computeActionFromQValues
        - getQValue
        - getAction
        - update

      Instance variables you have access to
        - self.epsilon (exploration prob)
        - self.alpha (learning rate)
        - self.discount (discount rate)

      Functions you should use
        - self.getLegalActions(state)
          which returns legal actions for a state
    """
    def __init__(self, **args):
        "You can initialize Q-values here..."
        ReinforcementAgent.__init__(self, **args)

        self.q_vals = util.Counter()

    def getQValue(self, state, action):
        """
          Returns Q(state,action)
          Should return 0.0 if we have never seen a state
          or the Q node value otherwise
        """
        "*** YOUR CODE HERE ***"
        Qnode = (state, action)
        return self.q_vals[Qnode]


    def computeValueFromQValues(self, state):
        """
          Returns max_action Q(state,action)
          where the max is over legal actions.  Note that if
          there are no legal actions, which is the case at the
          terminal state, you should return a value of 0.0.
        """
        "*** YOUR CODE HERE ***"
        # instantiate list of legal actions from state
        legal_actions = self.getLegalActions(state)

        # if we dont have any legal actions, we return a value of 0.0
        if len(legal_actions) == 0:
            return 0.0

        # initialize an empty list for vals
        vals = []
        # iterate through all actions in legal_actions
        for action in legal_actions:
            # append the relevant q value for each state, action pair
            vals.append(self.getQValue(state, action))

        # return the max q value
        return max(vals)

    def computeActionFromQValues(self, state):
        """
          Compute the best action to take in a state.  Note that if there
          are no legal actions, which is the case at the terminal state,
          you should return None.
        """
        "*** YOUR CODE HERE ***"
        # initialize an infinitesimally small value for the initial maxQ
        maxQ = float("-inf")
        # instantiate a list of legal_actions
        legal_actions = self.getLegalActions(state)

        # if we have no legal actions, we return a None action
        if len(legal_actions) == 0:
            return None

        # iterate through all actions available for the given state
        for action in self.getLegalActions(state):
            # grab the q value for the (state, action) pair
            Q = self.q_vals[(state, action)]

            # if we have a tie we make a random choice between the two actions
            if Q == maxQ:
                best = random.choice([best, action])

            # if our grabbed Q is larger than the current maxQ, we update maxQ
            # to be the Q value and make our best action the current action.
            elif Q > maxQ:
                maxQ = Q
                best = action

        # return the action associated with the largest q value
        return best

    def getAction(self, state):
        """
          Compute the action to take in the current state.  With
          probability self.epsilon, we should take a random action and
          take the best policy action otherwise.  Note that if there are
          no legal actions, which is the case at the terminal state, you
          should choose None as the action.

          HINT: You might want to use util.flipCoin(prob)
          HINT: To pick randomly from a list, use random.choice(list)
        """

        # get a legal
        legalActions = self.getLegalActions(state)

        # if there are no legal actions, return a None action
        if len(legalActions) == 0:
            return None

        # We flip a coin to determine if we use a random legal action or follow the current policy
        if util.flipCoin(self.epsilon):
            # This is the case where pacman decides to choose an action randomly from those available
            # to him
            return random.choice(legalActions)

        # This is the case where pacman decides to just follow the current policy
        return self.getPolicy(state)

    def update(self, state, action, nextState, reward):
        """
          The parent class calls this to observe a
          state = action => nextState and reward transition.
          You should do your Q-Value update here

          NOTE: You should never call this function,
          it will be called on your behalf
        """
        "*** YOUR CODE HERE ***"
        # Previous (state, action) pair value
        prev = (1.0 - self.alpha) * self.getQValue(state, action)
        # Reward value
        reward = self.alpha * reward
        # Initialize the current (state, action) piar
        current = (state, action)

        # Compute value of nextstate
        next = reward + prev + (self.alpha * self.discount * self.getValue(nextState))
        # Update the Q value
        self.q_vals[current] = next

    def getPolicy(self, state):
        return self.computeActionFromQValues(state)

    def getValue(self, state):
        return self.computeValueFromQValues(state)


class PacmanQAgent(QLearningAgent):
    "Exactly the same as QLearningAgent, but with different default parameters"

    def __init__(self, epsilon=0.05,gamma=0.8,alpha=0.2, numTraining=0, **args):
        """
        These default parameters can be changed from the pacman.py command line.
        For example, to change the exploration rate, try:
            python pacman.py -p PacmanQLearningAgent -a epsilon=0.1

        alpha    - learning rate
        epsilon  - exploration rate
        gamma    - discount factor
        numTraining - number of training episodes, i.e. no learning after these many episodes
        """
        args['epsilon'] = epsilon
        args['gamma'] = gamma
        args['alpha'] = alpha
        args['numTraining'] = numTraining
        self.index = 0  # This is always Pacman
        QLearningAgent.__init__(self, **args)

    def getAction(self, state):
        """
        Simply calls the getAction method of QLearningAgent and then
        informs parent of action for Pacman.  Do not change or remove this
        method.
        """
        action = QLearningAgent.getAction(self,state)
        self.doAction(state,action)
        return action


class ApproximateQAgent(PacmanQAgent):
    """
       ApproximateQLearningAgent

       You should only have to overwrite getQValue
       and update.  All other QLearningAgent functions
       should work as is.
    """
    def __init__(self, extractor='IdentityExtractor', **args):
        self.featExtractor = util.lookup(extractor, globals())()
        PacmanQAgent.__init__(self, **args)
        self.weights = util.Counter()

    def getWeights(self):
        return self.weights

    def getQValue(self, state, action):
        """
          Should return Q(state,action) = w * featureVector
          where * is the dotProduct operator
        """
        "*** YOUR CODE HERE ***"
        # Get the features for the current (state, action) pair
        features = self.featExtractor.getFeatures(state, action)

        # Compute Q value using provided formula
        q = sum([self.weights[feature] * features[feature] for feature in features])
        return q

    def update(self, state, action, nextState, reward):
        """
           Should update your weights based on transition
        """
        "*** YOUR CODE HERE ***"

        # Extract the features for the current (state, action) pair
        features = self.featExtractor.getFeatures(state, action)
        # Instantiate alpha
        a = self.alpha
        # instantiate discount
        g = self.discount
        # Compute the new value
        newval = (reward + (g * self.getValue(nextState))) - self.getQValue(state, action)

        # Iterate through all features and compute the weights for each feature
        for feature in features:
            self.weights[feature] = (self.weights[feature] + a * features[feature] * newval)

    def final(self, state):
        "Called at the end of each game."
        # call the super-class final method
        PacmanQAgent.final(self, state)

        # did we finish training?
        if self.episodesSoFar == self.numTraining:
            # you might want to print your weights here for debugging
            "*** YOUR CODE HERE ***"
            # Iterate through weights and print them for debugging purposes.
            for w in self.weights.keys():
                print("Weight: ", w)
                print("Value of weight:", self.weights[w])
