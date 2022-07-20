"""
Lab 3
Author: Cole Pendergraft, Jared Hall
Date: 2/22/2021
Description: Implements a binary search tree that stores MealTicket objects keyed by their ticketIDs.
"""
from mealticket import *

#============================== Aux Classes ====================================
class Sentinel():
    """This class builds the Sentinel nodes"""

    def __init__(self):
        """The constructor for the Sentinel class"""
        self._key = None
        self._value = None
        self._leftChild = None
        self._rightChild = None
        self._parent = None

    def isSentinel(self):
        """ This method makes it easy to check if a given node is a Sentinel"""
        return True

class Node():
    """ This class implements a node for the BST. """
    def __init__(self, ticket):
        """
        Description: The constructor for the Node class.
        Inputs: A valid MealTicket (input validation should be done by insert)
        """
        self._parent = Sentinel()
        self._leftChild = Sentinel()
        self._rightChild = Sentinel()
        self._value = ticket
        self._key = ticket.ticketID

    def __str__(self):
        """ Returns a string rep of the node (for debugging ^,^) """
        returnValue = "Node: {}\n".format(self._key)
        returnValue += "Parent: {}\n".format(self._parent._key)
        returnValue += "Left Child: {}\n".format(self._leftChild._key)
        returnValue += "Right Child: {}\n".format(self._rightChild._key)
        return returnValue

    def isSentinel(self):
        """ A helper method for figureing out if a node is a Sentinel """
        return False

    #Accessor Methods
    def getParent(self):
        """
        Description: Accessor method for the Node. Returns parent.
        """
        return self._parent

    def getRChild(self):
        """
        Description: Accessor method for the Node. Returns right child.
        """
        return self._rightChild

    def getLChild(self):
        """
        Description: Accessor method for the Node. Returns left child.
        """
        return self._leftChild

    def getValue(self):
        """
        Description: Accessor method for the Node. Returns the MealTicket.
        """
        return self._value

    # Mutator methods
    def setParent(self, node):
        """
        Description: Mutator method. Sets the parent reference.
        Input: A Node() reference.
        """
        self._parent = node

    def setLChild(self, node):
        """
        Description: Mutator method. Sets the lchild reference.
        Input: A Node() reference.
        """
        self._leftChild = node

    def setRChild(self, node):
        """
        Description: Mutator method. Sets the rchild reference.
        Input: A Node() reference.
        """
        self._rightChild = node

    #comparison operators
    def __gt__(self, other):
        """
        Description: Overloads the > operator to allow direct comparison of
                     nodes. Now we can do node1 > node2.
        Input: Another instance of the node class.
        """
        returnValue = False
        if(not self.isSentinel() and not other.isSentinel()):
            returnValue = self._key > other._key
        return returnValue

    def __lt__(self, other):
        """
        Description: Overloads the < operator to allow direct comparison of
                     nodes. Now we can do node1 < node2.
        Input: Another instance of the node class.
        """
        returnValue = False
        if(not self.isSentinel() and not other.isSentinel()):
            returnValue = self._key < other._key
        return returnValue

    def __eq__(self, other):
        """
        Description: Overloads the == operator to allow direct comparison of
                     nodes. Now we can do node1 == node2.
        Input: Another instance of the node class.
        """
        returnValue = False
        if(not self.isSentinel() and not other.isSentinel()):
            returnValue = self._key == other._key
        return returnValue

    def __ne__(self, other):
        """
        Description: Overloads the != operator to allow direct comparison of
                     nodes. Now we can do node1 != node2.
        Input: Another instance of the node class.
        """
        returnValue = False
        if(not self.isSentinel() and not other.isSentinel()):
            returnValue = self._key != other._key
        return returnValue

    def __le__(self, other):
        """
        Description: Overloads the <= operator to allow direct comparison of
                     nodes. Now we can do node1 <= node2.
        Input: Another instance of the node class.
        """
        returnValue = False
        if(not self.isSentinel() and not other.isSentinel()):
            returnValue = self._key <= other._key
        return returnValue

    def __ge__(self, other):
        """
        Description: Overloads the >= operator to allow direct comparison of
                     nodes. Now we can do node1 >= node2.
        Input: Another instance of the node class.
        """
        returnValue = False
        if(not self.isSentinel() and not other.isSentinel()):
            returnValue = self._key >= other._key
        return returnValue

    #Some helper methods to make things easy in the BST
    def hasLeftChild(self):
        """
        Description: This method returns true if the current node
                     has a left child
        """
        returnValue = False
        cond1 = not self._leftChild.isSentinel()
        cond2 = self._leftChild._parent is self
        if(cond1 and cond2):
                returnValue = True
        return returnValue

    def hasRightChild(self):
        """ This method returns true|false depending on if the current
            node has a right child or not."""
        returnValue = False
        cond1 = not self._rightChild.isSentinel()
        cond2 = self._rightChild._parent is self
        if(cond1 and cond2):
                returnValue = True
        return returnValue

    def hasOnlyOneChild(self):
        """ Returns True if the current node has only one child."""
        LC = self.hasLeftChild()
        RC = self.hasRightChild()
        return (LC and not RC) or (not LC and RC)

    def hasBothChildren(self):
        """ Returns True if the current node has both children"""
        return self.hasLeftChild() and self.hasRightChild()

    def isLeaf(self):
        """ Returns true if the current node is a leaf node."""
        returnValue = False
        if(self._rightChild.isSentinel() and self._leftChild.isSentinel()):
            returnValue = True
        return returnValue

    def isLeftChild(self):
        """Returns true if the current node is a left child"""
        cond1 = not self._parent.isSentinel()
        cond2 = self._parent._leftChild is self
        cond3 = self._parent._rightChild is not self
        return cond1 and cond2 and cond3

    def isRightChild(self):
        """Returns true if the current node is a right child"""
        cond1 = not self._parent.isSentinel()
        cond2 = self._parent._rightChild is self
        cond3 = self._parent._leftChild is not self
        return cond1 and cond2 and cond3

    def isRoot(self):
        """ Returns true if the current node is the root"""
        return self._parent.isSentinel()
#===============================================================================

#================================ BST Class ====================================
class BinarySearchTree:
    """
    Description: A Binary Search Tree (BST).
    Note: Algorithms for the BST can be found in ch. 12 of the book.
    """

    def __init__(self):
        """ The constructor for our BST """
        self._root = Sentinel()
        #Add any other instance variables you need.

    def _isValid(self, ticket):
        """
        Description: A method for checking if the given ticket is a valid
                     mealticket.
        Inputs: Some object in the variable ticket.
        Outputs: Boolean (True|False) depending on if it is a valid mealticket.
        """
        return type(ticket) == MealTicket

    def _findMinimum(self, node):
        """
        Description: Finds the minimum child of a tree when given a node.
        Inputs: A node from the BST.
        Outputs: The minumum node from the sub-tree (e.g the left-most child).
        """
        returnValue = False
        if not node.isSentinel():
            returnValue = node
            while not returnValue._leftChild.isSentinel():
                returnValue = returnValue._leftChild
        return returnValue

    def _findSuccessor(self, node):
        """
        Description: Given a node, returns the successor of that node,
                     or False if there is no successor.
        """
        successor = False
        # if node has a right child
        if(node.hasRightChild()):
            # then successor is the min of the right subtree
            successor = self._findMinimum(node._rightChild)
        elif(node._parent): # node has no right child, but has a parent
            if(node.isLeftChild()): # node is a left child
                successor = self._parent # then succ is the parent
            else: # node is right child, and has not right child
                successor = node._parent
                while not successor._parent.isSentinel() and node.isRightChild():
                    node = successor
                    successor = successor._parent
        return successor

    def _transplant(self, uNode, vNode):
        """
        Description: Replaces subtree at uNode with subtree at vNode.
        Note: See pg. 296 for description of the transplant routine.
        """
        if uNode == self._root:
            self._root = vNode
            uNode._leftChild = None
            uNode._rightChild = None
        elif uNode.isLeftChild():
            uNode._parent._leftChild = vNode
        else:
            uNode._parent._rightChild = vNode
        if vNode != None:
            vNode._parent = uNode._parent

    def _transplantR(self, cNode):
        """
        Description: This transplant attaches the currentNodes right child
                     to the current nodes parent.
        Notes:
                1. Do not call this method when cNode is the root.
                2. Don't forget to handle the cNodes references in your func.
        """
        parent = cNode.getParent()
        child = cNode.getRChild()
        if(cNode.isLeftChild()):
            parent.setLChild(child)
            child.setParent(parent)
        else:
            parent.setRChild(child)
            child.setParent(parent)

    def _transplantL(self, cNode):
        """
        Description: This transplant attaches the currentNodes right child
                     to the current nodes parent.
        Notes:
                1. Do not call this method when cNode is the root.
                2. Don't forget to handle the cNodes references in your func.
        """
        parent = cNode.getParent()
        child = cNode.getLChild()
        if(cNode.isLeftChild()):
            parent.setLChild(child)
            child.setParent(parent)
        else:
            parent.setRChild(child)
            child.setParent(parent)


    def traverse(self, mode):
        """
        Description: The traverse method returns a string rep
                     of the tree according to the specified mode
        """
        self.output = ""
        if(type(mode) == str):
            if(mode == "in-order"):
                self.inorder(self._root)
            elif(mode == "pre-order"):
                self.preorder(self._root)
            elif(mode == "post-order"):
                self.postorder(self._root)
        else:
            self.output = "  "
        return self.output[:-2]

    def inorder(self, node):
        """ computes the inorder traversal """
        if(not node.isSentinel()):
            self.inorder(node.getLChild())
            self.output += str(node._key) + ", "
            self.inorder(node.getRChild())

    def preorder(self, node):
        """computes the pre-order traversal"""
        if(not node.isSentinel()):
            self.output += str(node._key) + ", "
            self.preorder(node.getLChild())
            self.preorder(node.getRChild())

    def postorder(self, node):
        """ compute postorder traversal"""
        if(not node.isSentinel()):
            self.postorder(node.getLChild())
            self.postorder(node.getRChild())
            self.output += str(node._key) + ", "

    def insert(self, ticket):
        """
        Description: Inserts given MealTicket into the tree while
                     preserving binary tree property.
                     Returns True if successful, False otherwise
        """
        ret = False # Set our starting return

        if self._isValid(ticket):   # Check that we have a valid ticket
            node = Node(ticket)     # If we have a valid ticket, create a node for that ticket
            currentNode = self._root    # CN starts out as the root

            ret = True  # If we've gotten this far, everything will be fine
            if currentNode.isSentinel():   # If tree empty, insert at root
                self._root = node

            else:   # If our tree is not empty
                while True: # While loop will end when break statement is hit

                    # Case 1: Inserted ticketID less than CN ticketID
                    if node._key < currentNode._key:    # If our ticketID is less than CN ticket ID, we want to go left
                        if currentNode.hasLeftChild():  # Check if the CN has a left child
                            currentNode = currentNode._leftChild    # If yes, update CN to be CN.L, run loop again
                        else:   # If no left child
                            node.setParent(currentNode) # Set the CN to be the parent of the node
                            currentNode.setLChild(node) # Set the node to be the left child of CN
                            break   # Terminate loop

                    # Case 2: Inserted ticketID greater than CN ticketID
                    else:   # If our ticketID is greater than CN ticket ID, we want to go right
                        if currentNode.hasRightChild(): # Check if CN has a right child
                            currentNode = currentNode._rightChild   # If yes, update CN to be CN.R, run loop again
                        else:   # If CN doesn't have a right child
                            node.setParent(currentNode) # Set CN to be the parent of the node
                            currentNode.setRChild(node) # Set the node to be the right child of CN
                            break   # Terminate loop

        return ret

    def delete(self, ticketID):
        """
        Description: Deletes node from tree with given ticketID;
                     restructures binary tree. Returns True if successful,
                     False otherwise
        """
        result = False  # Start with a False result
        currentNode = self._find(ticketID)  # Find the node with the given ID
        if type(currentNode) is not bool:   # Checks to make sure find(ticketID) returns a MealTicket object

            result = True   # If this loop has been entered, we want to end up returning true


            if currentNode.isSentinel():    # If the current node is a sentinel then our BST is empty
                pass    # So we pass to false

            # Case 1: CN has no children
            if (currentNode.isLeaf()):  # If our CN has no children
                parent = currentNode.getParent() # Get the parent of CN

                # Sub-case 1: Current node is root
                if(currentNode == self._root):   # If the current node is the root
                    self._root = Sentinel() # Set the root to be a sentinel

                # Sub-case 2: Current node is a left child
                elif(currentNode.isLeftChild()):  # If the CN is a left child
                    parent.setLChild(Sentinel())    # Set the new left child to be a sentinel

                # Sub-case 3: Current node is a right child
                elif(currentNode.isRightChild()): # If the CN is a right child
                    parent.setRChild(Sentinel())    # Set the new right child to be a sentinel

            # Case 2: CN has only 1 child
            elif (currentNode.hasOnlyOneChild()):   # If our CN has only one child

                # Sub-case 1: If the child is a left child
                if(currentNode.hasLeftChild()): # If that child is a left child

                    # Sub-sub-case 1: If the CN is the root with a left child
                    if(currentNode == self._root):  # If the CN is the root and has a left child
                        self._root = currentNode.getLChild()    # Set the root to the left child

                    # Sub-sub-case 2: If CN is not the root, but has a left child
                    else:   # If CN is not the root
                        self._transplantL(currentNode)  # Transplant Left

                # Sub-case 2: If the child is a right child
                elif(currentNode.hasRightChild()):  # If our only child is a right child

                    # Sub-sub-case 1: If CN is the root and has a right child
                    if(currentNode == self._root):  # If CN is our root
                        self._root = currentNode.getRChild()    # Set right child to the root

                    # Sub-sub-case 2: If CN is not the root, but has a right child
                    else:   # If CN is not the root
                        self._transplantR(currentNode)  # Transplant Right

                currentNode.setParent(Sentinel()) # Removing parent pointer from CN
                currentNode.setLChild(Sentinel()) # Removing left child pointer from CN
                currentNode.setRChild(Sentinel()) # Removing right child pointer from CN

            # Case 3: CN has two children
            elif(currentNode.hasBothChildren()):    # If CN has two children
                succ = self._findSuccessor(currentNode) # Find the successor
                self.delete(succ._key) # Delete the key and value associated with the successor
                currentNode._value = succ._value    # Set the CN vale to the succ value, which is none after the delete
                currentNode._key = succ._key    # Set the CN key to the succ key, also None


        return result



    def find(self, ticketID):
        """
        Description: Finds node in tree with given ticketID,
                     returns corresponding ticket. Returns False if unsuccessful.
        """
        if(ticketID < 0) or (type(ticketID) != int):    # Only want positive integers
            return False

        else:
            currentNode = self._root    # Start with the root
            while(currentNode._key != ticketID):    # We want our loop to stop when the key for our CN matches the ID

                if(currentNode.isSentinel()):   # If the node is a sentinel, something has gone wrong
                    return False

                elif(ticketID < currentNode._key):  # If the ID is less than the key of CN, we go left
                    currentNode = currentNode.getLChild()   # New CN is the left child, run loop again

                elif(ticketID > currentNode._key):  # If the ID is greater than the key of CN, we go right
                    currentNode = currentNode.getRChild()   # New CN is the right child, run loop again

            ticket = currentNode.getValue()# Get the ticket associated with the ticketID
            return ticket  # Return the ticket


    def _find(self, ticketID):
        """
        Description: Helper method for find that returns the node at the ticketID
        """
        if(ticketID < 0) or (type(ticketID) != int):    # Only want positive integers
            return False

        else:
            currentNode = self._root    # Start with the root
            while(currentNode._key != ticketID):    # We want our loop to stop when the key for our CN matches the ID

                if(currentNode.isSentinel()):   # If the node is a sentinel, something has gone wrong
                    return False

                elif(ticketID < currentNode._key):  # If the ID is less than the key of CN, we go left
                    currentNode = currentNode.getLChild()   # New CN is the left child, run loop again

                elif(ticketID > currentNode._key):  # If the ID is greater than the key of CN, we go right
                    currentNode = currentNode.getRChild()   # New CN is the right child, run loop again

            return currentNode  # Return the CN
