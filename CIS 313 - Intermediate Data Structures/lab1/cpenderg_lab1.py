"""
Author: Cole Pendergraft
Description: Implementations of Queue and Stack classes using a linked list
Date: 01/26/2021
"""
from mealticket import *


class Node:
    """ A node class that stores information. Essential for linked list
    implementations. Will be used to implement both the Stack class
     and the Queue class """

    def __init__(self, data):
        """ Constructor for the node class """
        # We need a data variable to track the
        # ticket IDs
        self.data = data

        # We will need to track values next to our node
        # so we need to instantiate a next variable.
        self.next = None


class Queue:
    """ A queue class implemented using a linked list """

    def __init__(self, capacity):
        """ Constructor for the queue """
        self.maxSize = capacity  # maxSize will be passed in
        self.currentSize = 0  # Our queue starts as a size of 0
        self.head = None  # An empty queue has no head
        self.tail = None  # An empty queue has no tail

    def isEmpty(self):
        """ Function to check if our queue is empty """
        # If our currentSize = 0, then the queue is empty
        return self.currentSize == 0

    def isFull(self):
        """ Function to check if the queue is full """
        # If our currentSize = maxSize then our queue is full
        return self.currentSize == self.maxSize

    def enqueue(self, ticket):
        """ Adds elements to the queue """
        # We want to return false on invalid input
        if type(ticket) != MealTicket:
            return False

        # If our queue is full we can't insert anything
        elif self.isFull():
            return False

        else:
            # If we have valid input, we want to create a node
            # by calling .data on this node object we should
            # hopefully get back the ticket object
            node = Node(ticket)

            # Now we need to check if there are any elements already in the
            # queue so we can adjust our tail and head values accordingly.
            # Since queues insert at the tail, it is enough to check if we have
            # a tail or not. If we don't, then the queue is empty.
            if self.tail is None:
                # If our queue is empty, then the node we are inserting
                # will be both the head and the tail
                self.tail = node
                self.head = node
                self.currentSize += 1     # We have to grow our current size
                return True    # After inserting we are done

            # Now we need to account for the situation in which our queue is not
            # empty.
            # We assign the value next to the tail as the node, which
            # can be conceptualized as saying the value to the right of the
            # tail is now the node, which means the node is actually in the tail
            # position.
            self.tail.next = node

            # Now that node is "to the right" of the original tail, it has entered
            # the tail position so we want to reassign our tail to the new node.
            self.tail = node

            self.currentSize += 1    # We need to grow our current size
            return True    # Return True if successful

    def dequeue(self):
        """ Removes elements from the queue """
        # We first need to check if our queue is empty
        if self.isEmpty():
            return False

        # If our queue is not empty, we do the following
        else:
            # We create a temporary variable to hold our head
            # so that we can still access the data of head
            # after we have dequeued it.
            temp = self.head

            # Now we want our new head to be the one next to our current
            self.head = temp.next

            # Now our head value has been updated, so if we want to return
            # our head we must use temp, which has our original head
            # stored
            self.currentSize -= 1  # We have to shrink our current size
            return temp.data

    def front(self):
        """ Function that enables user to peek at the top element of the
        queue without removing it """
        # First we need to check if our queue is empty
        if self.isEmpty():
            return False

        # If our queue is not empty, then we want
        # to return the ticket associated with self.head
        # which will be self.head.data
        else:
            return self.head.data


# We can use the same node structure for the stack
class Stack:
    """ Implementation of a stack class using a linked list """

    def __init__(self, capacity):
        """ Constructor for the stack class """
        # Stacks insert and remove at the head, so no
        # tail needed.
        self.maxSize = capacity
        self.currentSize = 0
        self.head = None

    def isFull(self):
        """ Function to check if the stack is full """
        # The logic here is the same as the queue class
        return self.maxSize == self.currentSize

    def isEmpty(self):
        """ Function to check if the stack is empty """
        # The logic here is the same as the queue class
        return self.currentSize == 0

    def push(self, ticket):
        """ Function to add elements to the stack """
        # We need to ensure that we have a valid input
        if type(ticket) != MealTicket:
            return False

        # We need to check if the stack is full
        elif self.isFull():
            return False

        else:
            # The logic for creating this node is the same
            # as in the enqueue method for the queue class
            node = Node(ticket)

            # Now we have two considerations to make:
            # 1. If the stack is empty when we push
            # 2. If the stack is not empty when we push

            # Consideration 1:
            # If stack is empty, then self.head will not exist,
            # so we want the pushed value to be the new head:

            if self.head is None:
                self.head = node
                self.currentSize += 1  # Have to grow our stack
                return True  # True correlates to a successful push

            else:
                # Consideration 2:
                # If the stack is not empty, then we want our current head
                # to be moved to the position immediately to the right
                # and then make our node the new head

                node.next = self.head  # moving the current head "to the right"
                self.head = node  # Assigning the new node to the head

                # Now we should have our new node as the head, and the value
                # immediately following it will be the old head.
                self.currentSize += 1
                return True

    def pop(self):
        """ Function to remove and return elements from the stack """
        # We need to check if the stack is empty
        if self.isEmpty():
            return False

        else:
            # To pop, we want to remove the element at the head,
            # and then assign the value next to the head as the
            # new head

            temp = self.head   # Create a temporary var to hold head

            # Set our new head to be the value next to the original
            self.head = self.head.next

            # Now we can "remove" our original head by saying it has
            # no values next to it
            temp.next = None

            self.currentSize -= 1  # We have to shrink our current size
            return temp.data

    def peek(self):
        """ Function that enables the user to look at the top element
        without removing it """
        # The logic here is the same as the queue class
        if self.isEmpty():
            return False
        else:
            return self.head.data
