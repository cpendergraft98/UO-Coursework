"""
Lab 4 - Red Black Tree
Author: Cole Pendergraft, Jared Hall
Date: 02/14/2021
Description: A python implementation of a Red Black Tree
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
        self._color = "black"

    def isSentinel(self):
        """ This method makes it easy to check if a given node is a Sentinel"""
        return True

    def getColor(self):
        """
        Description: This method returns the color.
        """
        return self._color

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

    def setColor(self, color):
        """
        Description: This method sets the color
        """
        self._color = color

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

    def setParent(self, node):
        """
        Description: Mutator method. Sets the parent reference.
        Input: A Node() reference.
        """
        self._parent = node

class RBNode():
    """ This class implements a node for the RBT. """
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
        self._color = "red"

    def __str__(self):
        """ Returns a string rep of the node (for debugging ^,^) """
        returnValue = "Node: {}\n".format(self._key, self._color)
        returnValue += "Parent: {}\n".format(self._parent._key)
        returnValue += "Left Child: {}\n".format(self._leftChild._key)
        returnValue += "Right Child: {}\n".format(self._rightChild._key)
        return returnValue

    def isSentinel(self):
        """ A helper method for figureing out if a node is a Sentinel """
        return False

    #Accessor Methods
    def getColor(self):
        """
        Description: This method returns the color.
        """
        return self._color

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

    def setColor(self, color):
        """
        Description: This method sets the color
        """
        self._color = color

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
#===============================================================================

class RedBlackTree:
    """ Skeleton code for the red-black tree"""

    def __init__(self):
        """ The constructor for the red-black tree"""
        self._root = Sentinel()
        self._treeHeight = 0
        self.output = ""

    def _isRoot(self, node):
        """
        Description: This function returns true if the given node is the root.
        """
        return node is self._root

    def _isEmpty(self):
        """
        Description: This method returns true if the tree is empty, else False.
        """
        return self._root.isSentinel()

    def _isValid(self, ticket):
        """
        Description: A method for checking if the given ticket is a valid
                     mealticket.
        Inputs: Some object in the variable ticket.
        Outputs: Boolean (True|False) depending on if it is a valid mealticket.
        """
        return type(ticket) == MealTicket

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

    def colorPrint(self, node):
        if(not node.isSentinel()):
            self.output+="{"+str(node._key)+","+str(node._color)+"}"+", "
            #self.output += str(node._key) + ", "
            self.colorPrint(node.getLChild())
            self.colorPrint(node.getRChild())


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
            elif(mode == "color-print"):
                self.colorPrint(self._root)
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

    def _findMinimum(self, node):
        """
        Description: Finds the minimum child of a tree when given a node.
        Inputs: A node from the BST.
        Outputs: The minumum node from the sub-tree (e.g the left-most child).
        """
        returnValue = False
        if not node.isSentinel():
            returnValue = node
            while not returnValue.getLChild().isSentinel():
                returnValue = returnValue.getLChild()
        return returnValue

    def _findSuccessor(self, node):
        """
        Description: Given a node, returns the successor of that node,
                     or False if there is no successor.
        """
        succ = False
        # if node has a right child
        if(node.hasRightChild()):
            # then successor is the min of the right subtree
            succ = self._findMinimum(node._rightChild)
        # node has no right child, but has a parent
        elif(node.getParent().isSentinel()):
            if(node.isLeftChild()): # node is a left child
                succ = node.getParent() # then succ is the parent
            else: # node is right child, and has not right child
                succ = node.getParent()
                while not succ.getParent().isSentinel() and node.isRightChild():
                    node = successor
                    succ = successor.getParent()
        return succ

    #=========================== Manditory Methods =============================
    #You write these. I will update with BST solution on saturday.
    def find(self, ticketID):
        """ Hints: This method returns either a Mealticket or False
                   just like in the BST lab. Start at the root then make
                   your way to the RBNode whose ticketID matches the input.
                   Then return the value of that node.
        """
        ret = False
        if(type(ticketID) == int and ticketID > 0):
            currentNode = self._root
            while(not currentNode.isSentinel()):
                if(currentNode._key == ticketID):
                    ret = currentNode.getValue()
                    break
                elif(ticketID < currentNode._key):
                    currentNode = currentNode.getLChild()
                else:
                    currentNode = currentNode.getRChild()
        return ret

    def delete(self, ticketID):
        """ The delete method starts out the same as BST but then you need
            to restructure your RBT.
        """
        ret = False
        if(type(ticketID) == int and ticketID > 0):
            currentNode = self.findNode(ticketID)
            if(type(currentNode) == RBNode):
                ret = True
                #Step-01: If the node is a leaf - just delete it
                if(currentNode.isLeaf()):
                    sen = Sentinel() # Create a sentinel instance
                    parent = currentNode.getParent()

                    # If CN is the root
                    if(currentNode is self._root):
                        self._root = sen

                    # If CN is the left child
                    elif(currentNode.isLeftChild()):
                        parent.setLChild(sen)
                        sen.setParent(parent)

                    # If CN is the right child
                    else:
                        parent.setRChild(sen)
                        sen.setParent(parent)

                    # If the CN color is black we need to restructure
                    if(currentNode.getColor() == "black"):
                        self.deleteFixup(sen)

                    currentNode.setParent(None)
                    currentNode.setLChild(None)
                    currentNode.setRChild(None)

                #Step-02: If the node has only one child then transplant
                elif(currentNode.hasOnlyOneChild()):

                    # If CN has a LC
                    if(currentNode.hasLeftChild()):
                        child = currentNode.getLChild()

                        # If CN is the root
                        if(currentNode is self._root):
                            self._root = currentNode.getLChild()

                        # Transplant L
                        else:
                            self._transplantL(currentNode)

                    # If CN has a RC
                    else:
                        child = currentNode.getRChild()

                        # If CN is the root
                        if(currentNode is self._root):
                            self.root = currentNode.getRChild()

                        # Transplant R
                        else:
                            self._transplantR(currentNode)

                    # If CN color is black we need to resturcture
                    if(currentNode.getColor() == "black"):
                        self.deleteFixup(child)

                    currentNode.setParent(None)
                    currentNode.setLChild(None)
                    currentNode.setRChild(None)

                #Step-03: If the node has both children - Find successor
                else:
                    successor = self._findSuccessor(currentNode)
                    self.delete(successor._key)
                    currentNode._value = successor._value
                    currentNode._key = successor._key

        return ret

    def insert(self, ticket):
        """
        Hints: add a key to the tree. Don't forget to fix up the tree
        and balance the nodes.
        """
        ret = False
        if(self._isValid(ticket)):
            newNode = RBNode(ticket)
            ret = True
            if(self._root.isSentinel()):
                self._root = newNode
            else:
                currentNode = self._root

                # While the CN is not a Sentinel()
                while(not currentNode.isSentinel()):

                    # If NN <= CN
                    if(newNode <= currentNode):
                        lChild = currentNode.getLChild()
                        if(lChild.isSentinel()):
                            currentNode.setLChild(newNode)
                            newNode.setParent(currentNode)
                            currentNode = Sentinel()
                        else:
                            currentNode = lChild

                    # If NN <= CN
                    else:
                        rChild = currentNode.getRChild()
                        if(rChild.isSentinel()):
                            currentNode.setRChild(newNode)
                            newNode.setParent(currentNode)
                            currentNode = Sentinel()
                        else:
                            currentNode = rChild

            # Now that everything is inserted, we just need to fixup the
            # tree
            self.insertFixup(newNode)
        return ret

    #========================== Additional Methods =============================
    #I think these are useful. Implement them if you want.
    def findNode(self, ticketID):
        """
        Hints: This method finds a node and returns it or
               false if no node is found. First do a BST search for the RBNode
               with the same key as the input ticketID. Then return that node.
        """
        #similar to find but returns a node (used internally for find sucessor
        # and delete). Same steps as above, just return currentNode
        ret = False
        if(type(ticketID) == int and ticketID > 0):
            currentNode = self._root
            while(not currentNode.isSentinel()):
                if(currentNode._key == ticketID):
                    ret = currentNode # Return the node instead of the ticketID
                    break
                elif(ticketID < currentNode._key):
                    currentNode = currentNode.getLChild()
                else:
                    currentNode = currentNode.getRChild()
        return ret

    def insertFixup(self, currentNode):
        """Hint: write a function to balance your tree after inserting"""
        while((currentNode.getColor() == "red") and (currentNode.getParent().getColor() == "red")):
            p = currentNode.getParent()
            gp = p.getParent()

            # Question 1: is the P a left child?
            if p.isLeftChild():
                unc = gp.getRChild()

                # Case 1: The unc is red
                if (unc.getColor() == "red"):
                    gp.setColor("red")
                    p.setColor("black")
                    unc.setColor("black")
                    currentNode = gp

                # Case 2: The unc is black
                else:
                    # Sub-case 1: if current node is a right child
                    if(currentNode.isRightChild()):
                        currentNode = p
                        self.leftRotate(currentNode)
                        p = currentNode.getParent()
                        gp = p.getParent()

                    p.setColor("black")
                    gp.setColor("red")
                    self.rightRotate(gp)

            # Question 2: is the P a right child?
            else:
                unc = gp.getLChild()

                # Case 1: The unc is red
                if(unc.getColor() == "red"):
                    gp.setColor("red")
                    p.setColor("black")
                    unc.setColor("black")
                    currentNode = gp

                # Case 2: The unc is black
                else:
                    # Sub-case 1: If current node is a left child
                    if(currentNode.isLeftChild()):
                        currentNode = p
                        self.rightRotate(currentNode)
                        p = currentNode.getParent()
                        gp = p.getParent()

                    p.setColor("black")
                    gp.setColor("red")
                    self.leftRotate(gp)

        self._root.setColor("black")

    def deleteFixup(self, currentNode):
        """
        Hint: receives a node and fixes up the tree,
              balancing from that node.
        """
        while((currentNode.getColor() == "black") and (currentNode is not self._root)):
            # Question 1: is CN a leftchild?
            if(currentNode.isLeftChild()):
                sib = currentNode.getParent().getRChild()
                # Case 1: is the sibling red?
                if(sib.getColor() == "red"):
                    sib.setColor("black")
                    currentNode.getParent().setColor("red")
                    self.leftRotate(currentNode.getParent())
                    sib = currentNode.getParent().getRChild()
                # case 2: Are both sibs children black?
                if((sib.getRChild().getColor() == "black") and (sib.getLChild().getColor() == "black")):
                    if(not sib.isSentinel()):
                        sib.setColor("red")
                        currentNode = currentNode.getParent()

                # Case 3:
                else:
                    #sub-case: sib right child is Black
                    if(sib.getRChild().getColor() == "black"):
                        sib.getLChild().setColor("black")
                        sib.setColor("red")
                        self.rightRotate(sib)
                        sib = currentNode.getParent().getRChild()
                    sib.setColor(currentNode.getParent().getColor())
                    currentNode.getParent().setColor("black")
                    sib.getRChild().setColor("black")
                    self.leftRotate(currentNode.getParent())
                    currentNode = self._root

            # Question 2: is CN a right child?
            else:
                sib = currentNode.getParent().getLChild()
                # Case 1: Sib is Red
                if(sib.getColor() == "red"):
                    sib.setColor("black")
                    currentNode.getParent().setColor("red")
                    self.rightRotate(currentNode.getParent())
                    sib = currentNode.getParent().getLChild()

                # Case 2: Are both sibs children black?
                if((sib.getRChild().getColor() == "black") and (sib.getLChild().getColor() == "black")):
                    if(not sib.isSentinel()):
                        sib.setColor("red")
                        currentNode = currentNode.getParent()

                # Case 3:
                else:
                    #sub-case: sib left child is black
                    if(sib.getLChild().getColor() == "black"):
                        sib.getRChild().setColor("black")
                        sib.setColor("red")
                        self.leftRotate(sib)
                        sib = currentNode.getParent().getLChild()
                    sib.setColor(currentNode.getParent().getColor())
                    currentNode.getParent().setColor("black")
                    sib.getLChild().setColor("black")
                    self.rightRotate(currentNode.getParent())
                    currentNode = self._root
        currentNode.setColor("black")


    def leftRotate(self, currentNode):
        """ perform a left rotation from a given node"""
        rchild = currentNode.getRChild()
        p = currentNode.getParent()
        lgrandchild = rchild.getLChild()

        # set lgrandchild
        currentNode.setRChild(lgrandchild)
        if(lgrandchild is not None) and (not lgrandchild.isSentinel()):
            lgrandchild.setParent(currentNode)

        # set rchild
        rchild.setParent(p)
        if(p.isSentinel()): # means that CN is the Root
            self._root = rchild
        elif(currentNode.isLeftChild()):
            p.setLChild(rchild)
        else:
            p.setRChild(rchild)

        # set CurrentNode
        rchild.setLChild(currentNode)
        currentNode.setParent(rchild)

    def rightRotate(self, currentNode):
        """ perform a right rotation from a given node"""
        lchild = currentNode.getLChild()
        p = currentNode.getParent()
        rgrandchild = lchild.getRChild()

        # set rgrandchild
        currentNode.setLChild(rgrandchild)
        if(rgrandchild is not None) and (not rgrandchild.isSentinel()):
            rgrandchild.setParent(currentNode)

        # set lChild
        lchild.setParent(p)
        if(p.isSentinel()): # measn that CN is the Root
            self._root = lchild
        elif(currentNode.isRightChild()):
            p.setRChild(lchild)
        else:
            p.setLChild(lchild)

        # set CurrentNode
        lchild.setRChild(currentNode)
        currentNode.setParent(lchild)
