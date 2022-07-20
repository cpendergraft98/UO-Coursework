"""
CIS 313 Lab 2

Author: Cole Pendergraft

Notes: For whatever reason, it seems that my prio queue only works something like 90% of the time. If I execute the
provided main, the queue is built and sometimes it is structured properly, and other times it isn't. I have thus far
been unable to determine why the ordering fails. I assume it has something to do with heapify, but I can't determine
what it is.
"""

from mealticket import *


class PriorityQueue:
    """ Priority Queue Object """

    def __init__(self, capacity):
        self._maxSize = capacity    # maxSize is passed in
        self._currentSize = 0   # Empty queue has a size of zero
        self._heap = [None] * (self._maxSize + 1)   # Establish an empty heap of size maxsize + 1. Using 1 indexing

    def __str__(self): # Adjustments had to be made in order to accompany the 1 indexing
        """
        Author: Jared Hall
        Date: 01/03/2020
        Description: Output the current queue as a string.
        Inputs: None
        Outputs: str
        """
        returnValue = "Current queue: ["
        if (self._currentSize != 0):
            for ticket in self._heap:
                if (ticket is None):
                    continue    # Changed from a break statement to continue, this way the code doesn't terminate when
                                # the object at index 0 is passed in.
                else:
                    returnValue += "(" + str(ticket.ticketID) + ", "
                    returnValue += str(ticket.totalCost) + "), "
            returnValue = returnValue[:-2] + "]"
        else:
            returnValue += "]"
        return returnValue

    def enqueue(self, ticket):
        """ Inserts a new MealTicket object into our heap """
        if type(ticket) != MealTicket:  # Crash on invalid input
            print("Invalid input.")
            return False

        elif self.isFull(): # Crash on a full queue
            return False

        self._currentSize += 1  # Grow heap size
        self._heap[self._currentSize] = ticket  # Insert ticket element at the max index so we can check it against
                                                # all tickets above.

        index = self._currentSize
        parent_index = self._getParent(index)

        # Line below Checks if the current node has a larger priority than its parent. We check that index > 1 because
        # of our 1 indexing
        while(index > 1) and (self._heap[index].ticketID > self._heap[parent_index].ticketID):

            self._swap(index, parent_index) # If current node has a larger priority, swap it with parent
            index = parent_index    # Index of new object is the same as the former parent index

        return True # Returns true when ticket element has a lower priority than parent

    def dequeueMax(self):
        """ Removes and returns the max element of the heap """
        if self.isEmpty():  # Can't dequeue a ticket from an empty queue
            return False

        ret = self._heap[1] # We are indexing at 1, so the highest priority element will be at index 1
        self._heap[1] = self._heap[self._currentSize]   # Move the element of least priority to the highest priority
        self._currentSize -= 1  # Shrink the size of the heap
        self._heapify(1)    # Restructure heap using element of least priority. This should check the element against
                            # all others and restructure the heap as needed. This is also because heapify doesn't
                            # work if element passed in is a leaf.
        return ret  # Return the item that used to be at max priority

    def peekMax(self): # DONE
        """ Returns the max element of the heap without removal """
        if self.isEmpty():  # Can't peek at an element in an empty queue
            return False

        return self._heap[1]    # We are 1 indexing, so element at max priority is at index 1

    def isEmpty(self):
        """ Checks if our heap is empty """
        return (self._currentSize == 0) # Our queue is empty if the current size is still set to 0

    def isFull(self):
        """ Checks if our heap is full """
        return (self._currentSize == self._maxSize) # Our queue is full if the current size is equal to the max size

    def _heapify(self, index):
        """ Makes a heap """
        if self._isLeaf(index) == False:    # Leaves don't have children, so we need to make sure that the value passed
                                            # is a parent

            # If statement below checks if the current ticket priority is less than its children
            if(self._heap[index].ticketID < self._heap[self._leftChild(index)].ticketID) or \
                    (self._heap[index].ticketID < self._heap[self._rightChild(index)].ticketID):

                # If the current ticket is a lower priority, we need to find out which of it's children has the
                # highest priority. The statement below checks if the left child has a higher priority than the right
                if(self._heap[self._leftChild(index)].ticketID > self._heap[self._rightChild(index)].ticketID):
                    self._swap(index, self._leftChild(index))   # If the left child has a higher priority, we swap
                                                                # it with its parent index.
                    self._heapify(self._leftChild(index))   # Restructure the heap to check if the left child should be
                                                            # moved further
                else:
                    self._swap(index, self._rightChild(index))  # If the right child has a higher priority, we swap it
                                                                # with its parent index
                    self._heapify(self._rightChild(index))  # Restructure the heap to check if the right child should
                                                            # be moved further

    def _isLeaf(self, index): # DONE
        """ Checks if node at index is a leaf """
        if (index >= ((self._currentSize)//2)) and (index <= (self._currentSize)):  # If the element is at the very
                                                                                    # end of the heap, it is a leaf
            return True
        else:
            return False

    def _swap(self, index1, index2):
        """ Swaps the node at the index1 with the node at index2 """
        temp = self._heap[index1]   # Store the value at index1 in a temporary variable
        self._heap[index1] = self._heap[index2] # Change the value stored in index 1 to the value in index2
        self._heap[index2] = temp   # Change the value stored in index2 to the value in index1

    def _getParent(self, index):
        """ Returns the index of the parent of the node at the index passed in """
        return (index)//2   # Indexing at 1, so our parent node is the index//2

    def _leftChild(self, index):
        """ Returns the index of the left child of the node at index """
        return (2*index)    # Indexing at 1, so our left child is at 2 * index

    def _rightChild(self, index):
        """ Returns the index of the right child of the node at index """
        return(2*index) + 1 # Indexing at 1, so our right child is at 2*index + 1
