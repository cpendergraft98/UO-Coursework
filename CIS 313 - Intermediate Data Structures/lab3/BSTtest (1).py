from mealticket import *
from cpenderg_lab3 import *
import random


def bstTypeNoneCheck(bst, testType):
    if type(bst) != BinarySearchTree:
        print(f"The given BST is not a valid Binary Search Tree Type, happened in {testType} test")
        return False
    elif bst._root.isSentinel():
        print(f"The root is None or Sentinel(), check your insertion, happened in {testType} test")
        return False


def bstPrint(bst):
    print("\n")
    print("Printing pre-Order")
    print(bst.traverse("pre-order"))

    print("Printing in-Order")
    print(bst.traverse("in-order"))

    print("Printing post-Order")
    print(bst.traverse("post-order"))
    print("\n")

def preOrderPrint(bst):
    print("Printing pre-Order")
    print(bst.traverse("pre-order"))

def insertTest(bst, ticketList):

    print("------Test to check if insertion is completed")
    ticketPrint = ""
    for ticket in ticketList:
        result = bst.insert(ticket)
        ticketPrint += (str(ticket.ticketID) + ", ")
        if not result:
            print("---Insertion test Failed---")
            break

    if result:
        print("Multiple Insertion test successful")

def fixedInsertionTest():
    print("------Inserting fixed elements to see if the result is correct")
    ids = [22,2,1,20,5,16,9,8,24]
    tickets = generateFixedTickets(ids)
    bst = BinarySearchTree()
    for ticket in tickets:
        bst.insert(ticket)

    if bst.traverse("pre-order") != "22, 2, 1, 20, 5, 16, 9, 8, 24":
        print("Insertion test failed, inserts but doesnt insert correctly\n")
    else:
        print("Insertion test successful, insertions are correct NICE!\n")

def findTest(bst, ticketList):

    # if not bstTypeNoneCheck(bst, "find"):
    #     return False
    print("------Find test, checking to find half of the inserted tickets, and that many nonexistent tickets")
    topNumber = 31
    for ticket in ticketList[5:]:
        print(f"Testing to find {ticket.ticketID}")
        print(f"Result: {bst.find(ticket.ticketID).ticketID}, expected: {ticket.ticketID}\n")
        print(f"Testing to find {topNumber}, nonexistent node")
        print(f"Result: {bst.find(topNumber)}, expected: False\n")
        topNumber += 1

def deleteTest(bst, ticketList):
    print("------Delete test, trying to delete half of the inserted tickets, and that many nonexistent tickets")
    topNumber = 31
    print("Initial BST:")
    preOrderPrint(bst)
    print("\n")
    testCount = 1
    noError = True
    errorIndexes = []
    randomTicketIndex = random.sample(range(1, 10), 5)
    for index in range(5):

        ticket = ticketList[randomTicketIndex[index]]

        print(f"Testing to delete {ticket.ticketID}")
        deleteResult = bst.delete(ticket.ticketID)
        print(f"Result: {deleteResult}, expected: True")

        if noError and deleteResult is False:
            errorIndexes.append(ticket.ticketID)
            noError = False

        print("\n")
        print(f"Testing to delete {topNumber}, nonexistent node")
        deleteResult = bst.delete(topNumber)
        print(f"Result: {deleteResult}, expected: False")

        if noError and deleteResult == True:
            noError = False
        print("\n")
        topNumber += 1
        testCount += 1

    if not noError:
        print(f"Test {testCount} is failed at {errorIndexes} removals ")
    if noError:
        print(f"Delete test is successful")

def deleteTestWithoutComment(bst, ticketList):

    topNumber = 31
    noError = True
    errorIndexes = []
    randomTicketIndex = random.sample(range(1, 10), 5)
    for index in range(5):

        ticket = ticketList[randomTicketIndex[index]]

        deleteResult = bst.delete(ticket.ticketID)

        if noError and deleteResult is False:
            errorIndexes.append(ticket.ticketID)
            noError = False

        deleteResult = bst.delete(topNumber)

        if noError and deleteResult == True:
            noError = False
        topNumber += 1

    return noError

def aLotofDeleteTests():

    print("------This is the bossfight, 2000 tests to see if any errors happen while deleting,\n this "
          "doesnt guarantee correct deletion, but only looks for"
          "bugs, check the deletion type test above for accuracy\n")
    allCorrect = True
    testCount = 1
    for i in range(2000):
        testList = generateUniqueTickets()
        tree = BinarySearchTree()
        insertTickets(tree, testList)
        noError = deleteTestWithoutComment(tree, testList)

        if not noError:
            #print(f"Mistake in deleting elements in the tree:")
            #preOrderPrint(tree)
            allCorrect = False

    if allCorrect:
        print("2000 Delete Tests performed, all successful, if you survive this you probably are fine lol")
        testCount += 1
    else:
        print("Error happened with deletion")

def insertTickets(bst, tickets):
    for ticket in tickets:
        bst.insert(ticket)

def generateUniqueTickets():
    ticketIDList = [5,3,7,4,2,1,10,8,12]
    mealtickets = []
    randomTicketList = random.sample(range(1, 30), 10)
    for id in randomTicketList:
        ticket = MealTicket("Jared's Meal " + str(id))
        ticket.ticketID = id
        ticket.addItem(("Item 1", round(uniform(0, 30), 2)))
        ticket.addItem(("Item 2", round(uniform(0, 30), 2)))
        ticket.addItem(("Item 3", round(uniform(0, 30), 2)))
        mealtickets.append(ticket)
    return mealtickets

def generateFixedTickets(list):
    mealtickets = []
    randomTicketList = random.sample(range(1, 30), 10)
    for id in range(len(list)):
        ticket = MealTicket("Jared's Meal " + str(id))
        ticket.ticketID = list[id]
        ticket.addItem(("Item 1", round(uniform(0, 30), 2)))
        ticket.addItem(("Item 2", round(uniform(0, 30), 2)))
        ticket.addItem(("Item 3", round(uniform(0, 30), 2)))
        mealtickets.append(ticket)
    return mealtickets

def emptyInsertTest():
    print("------Empty Insert Test, inserting a ticket into empty BST")
    ids = [10]
    ticket = generateFixedTickets(ids)
    bst = BinarySearchTree()
    result = bst.insert(ticket[0])
    if result:
        print("Empty Insert Successful\n")
    else:
        print("Empty insert Failed\n")

def rootDeleteTest():
    print("------Root delete Test, deleting the root which is the single element")
    ids = [10]
    ticket = generateFixedTickets(ids)
    bst = BinarySearchTree()
    bst.insert(ticket[0])
    result = bst.delete(ticket[0].ticketID)

    if result:
        print("Root delete Successful\n")
    else:
        print("Root delete Failed\n")

def fixedDeleteTest():
    print("------Fixed BST Delete test, testing 3 types of deletion")
    idList = [22,2,1,20,5,16,9,8,24]
    bst = BinarySearchTree()
    tickets = generateFixedTickets(idList)
    result = True
    for ticket in tickets:
        #print(ticket.ticketID)
        bst.insert(ticket)

    bst.delete(1)
    if bst.traverse("pre-order") != "22, 2, 20, 5, 16, 9, 8, 24":
        print("Deletion of a leaf FAILED")
        result = False
    else:
        print("Deletion of a leaf SUCCESS")

    bst.delete(9)
    if bst.traverse("pre-order") != "22, 2, 20, 5, 16, 8, 24":
        print("Deletion of a node with single child FAILED")
        result = False
    else:
        print("Deletion of a node with single child SUCCESS")


    ids = [1]
    ticket = generateFixedTickets(ids)
    bst.insert(ticket[0])

    bst.delete(2)
    if bst.traverse("pre-order") != "22, 5, 1, 20, 16, 8, 24":
        print("Deletion of a node with two children FAILED\n")
        result = False
    else:
        print("Deletion of a node with two child SUCCESS\n")

    if result:
        print("Delete Type tests Successful\n")
    else:
        print("Delete type tests Failed\n")



def main():
    ticketList = generateMealTickets(10)
    fixedList = generateUniqueTickets()
    bst = BinarySearchTree()

    insertTest(bst, fixedList)
    print("\n")

    fixedInsertionTest()

    findTest(bst, fixedList)

    emptyInsertTest()

    rootDeleteTest()

    fixedDeleteTest()

    print("\n")
    deleteTest(bst, fixedList)
    print("\n")
    aLotofDeleteTests()








main()
