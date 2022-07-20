from mealticket import *
from cpenderg_lab4 import *
import random

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


def basicInsertTest():
    print("------Insert Test, inserting 3 elements------")
    ids = [5,3,7]
    tickets = generateFixedTickets(ids)
    rbt = RedBlackTree()
    for ticket in tickets:
        rbt.insert(ticket)

    if rbt.traverse("color-print") != "{5,black}, {3,red}, {7,red}":
        print("Insertion test FAILED, check your insertFixup")
        print("Output:", rbt.traverse("color-print"), "Expected: " , "{5,black}, {3,red}, {7,red}")
    else:
        print("Basic insertion test SUCCESS")

def biggerInsertTest():
    print("------Bigger Insert Test, inserting a lot of elements------")
    ids = [12,5,15,3,10,4,7,11,6,8,13,17,14]
    tickets = generateFixedTickets(ids)
    rbt = RedBlackTree()
    for ticket in tickets:
        rbt.insert(ticket)

    if rbt.traverse("color-print") != "{12,black}, {5,black}, {3,black}, {4,red}," \
                                      " {10,red}, {7,black}, {6,red}, {8,red}, {11,black}," \
                                      " {15,black}, {13,black}, {14,red}, {17,black}, ":
        print("Bigger insertion test FAILED, check your insertFixup")
        print("Output:", rbt.traverse("color-print"), "\nExpected:" , "{12,black}, {5,black}, {3,black}, {4,red}," \
                                      " {10,red}, {7,black}, {6,red}, {8,red}, {11,black}," \
                                      " {15,black}, {13,black}, {14,red}, {17,black}, ")
    else:
        print("Bigger insertion test SUCCESS")

def biggerInsertTest2():
    print("------Bigger Insert Test, inserting a lot of elements------")
    ids = [13,8,1,11,6,17,15,25,22,27]
    tickets = generateFixedTickets(ids)
    rbt = RedBlackTree()
    for ticket in tickets:
        rbt.insert(ticket)

    if rbt.traverse("color-print") != "{13,black}, {8,red}, {1,black}, {6,red}," \
                                    " {11,black}, {17,red}, {15,black}, {25,black}, {22,red}, {27,red}":

        print("Bigger insertion test FAILED, check your insertFixup")
        print("Output:", rbt.traverse("color-print"), "\nExpected:", "{13,black}, {8,red}, {1,black}, {6,red}," \
                                                                     " {11,black}, {17,red}, {15,black}, {25,black}, {22,red}," \
                                                                     " {27,red}")
    else:
        print("Bigger insertion test SUCCESS")

def biggerInsertTest3():
    print("\n------Bigger Insert Test, inserting a lot of elements------")
    ids = [61,52,85,20,55,16,76,71,65,81,93,90,101]
    tickets = generateFixedTickets(ids)
    rbt = RedBlackTree()
    for ticket in tickets:
        rbt.insert(ticket)

    if rbt.traverse("color-print") != "{61,black}, {52,black}, {85,black}, {20,black}," \
                                    " {16,red}, {55,black}, {76,red}, {71,black}, {65,red}, {81,black}, {93,red}," \
                                      " {90,black}, {101,black}":

        print("Bigger insertion test FAILED, check your insertFixup")
        print("Output:", rbt.traverse("color-print"), "\nExpected:", "{61,black}, {52,black}, {85,black}, {20,black}," \
                                    " {16,red}, {55,black}, {76,red}, {71,black}, {65,red}, {81,black}, {93,red}," \
                                      " {90,black}, {101,black}")
    else:
        print("Bigger insertion test SUCCESS")

def stepByStepInsertion():
    print("\n--------Step by step Insertion test, all prints are pre-order--------")
    rbt = RedBlackTree()
    ids = [8, 18, 5, 15, 17, 25, 40, 80]
    tickets = generateFixedTickets(ids)
    print("Inserting 8")
    rbt.insert(tickets[0])

    allCorrect = True

    print("Output:", rbt.traverse("color-print"), "\nExpected: {8,black}")
    if rbt.traverse("color-print") == "{8,black}":
        print("Insertion of 8 to the root SUCCESS")
    else:
        print("Insertion of 8 to the root FAILED")
        allCorrect = False

    print("\nInserting 18")
    rbt.insert(tickets[1])
    print("Output:", rbt.traverse("color-print"), "\nExpected: {8,black}, {18,red}")
    if rbt.traverse("color-print") == "{8,black}, {18,red}":
        print("Insertion of 18 SUCCESS")
    else:
        print("Insertion of 18 FAILED")
        allCorrect = False

    print("\nInserting 5")
    rbt.insert(tickets[2])
    print("Output:", rbt.traverse("color-print"), "\nExpected: {8,black}, {5,red}, {18,red}")
    if rbt.traverse("color-print") == "{8,black}, {5,red}, {18,red}":
        print("Insertion of 5 SUCCESS")
    else:
        print("Insertion of 5 FAILED")
        allCorrect = False

    print("\nInserting 15")
    rbt.insert(tickets[3])
    print("Output:", rbt.traverse("color-print"), "\nExpected: {8,black}, {5,black}, {18,black}, {15,red}")
    if rbt.traverse("color-print") == "{8,black}, {5,black}, {18,black}, {15,red}":
        print("Insertion of 15 SUCCESS")
    else:
        print("Insertion of 15 FAILED")
        allCorrect = False

    print("\nInserting 17")
    rbt.insert(tickets[4])
    print("Output:", rbt.traverse("color-print"), "\nExpected: {8,black}, {5,black}, {17,black}, {15,red}, {18,red}")
    if rbt.traverse("color-print") == "{8,black}, {5,black}, {17,black}, {15,red}, {18,red}":
        print("Insertion of 17 SUCCESS")
    else:
        print("Insertion of 17 FAILED")
        allCorrect = False

    print("\nInserting 25")
    rbt.insert(tickets[5])
    print("Output:", rbt.traverse("color-print"), "\nExpected: {8,black}, {5,black}, {17,red}, {15,black}, {18,black}, {25,red}")
    if rbt.traverse("color-print") == "{8,black}, {5,black}, {17,red}, {15,black}, {18,black}, {25,red}":
        print("Insertion of 25 SUCCESS")
    else:
        print("Insertion of 25 FAILED")
        allCorrect = False

    print("\nInserting 40")
    rbt.insert(tickets[6])
    print("Output:", rbt.traverse("color-print"), "\nExpected: {8,black}, {5,black}, {17,red}, {15,black}, {25,black}, {18,red}, {40,red}")
    if rbt.traverse("color-print") == "{8,black}, {5,black}, {17,red}, {15,black}, {25,black}, {18,red}, {40,red}":
        print("Insertion of 40 SUCCESS")
    else:
        print("Insertion of 40 FAILED")
        allCorrect = False

    print("\nInserting 80")
    rbt.insert(tickets[7])
    print("Output:", rbt.traverse("color-print"), "\nExpected: {17,black}, {8,red}, {5,black}, {15,black}, {25,red}, {18,black}, {40,black}, {80,red}")
    if rbt.traverse("color-print") == "{17,black}, {8,red}, {5,black}, {15,black}, {25,red}, {18,black}, {40,black}, {80,red}":
        print("Insertion of 80 SUCCESS")
    else:
        print("Insertion of 80 FAILED")
        allCorrect = False


    if allCorrect:
        print("\nYour insertion look alright ngl, YOU GOT IT")
    else:
        print("\nSum Ting Wong has visited your lab")


def deleteTestRedLeaf():
    print("\n------ Red Leaf Delete Test -------")
    rbt = RedBlackTree()
    ids = [8, 18, 5, 15, 17, 25, 40, 80]
    tickets = generateFixedTickets(ids)
    for ticket in tickets:
        rbt.insert(ticket)

    allCorrect = True

    print("Tree:", rbt.traverse("color-print"))
    print("Deleting red leaf 80\n")
    rbt.delete(80)
    print("Output:", rbt.traverse("color-print"), "\nExpected:","{17,black}, {8,red}, {5,black}, {15,black}, {25,red}, {18,black}, {40,black}" )

    if rbt.traverse("color-print") == "{17,black}, {8,red}, {5,black}, {15,black}, {25,red}, {18,black}, {40,black}":
        print("Deletion of 80, a single red leaf is SUCCESS")
    else:
        print("Insertion of 80, a single red leaf FAILED")
        allCorrect = False

    return allCorrect


def deleteTestRedSingle():
    print("\n------ Black with Single Red Child Delete Test -------")
    rbt = RedBlackTree()
    ids = [8, 18, 5, 15, 17, 25, 40, 80]
    tickets = generateFixedTickets(ids)
    for ticket in tickets:
        rbt.insert(ticket)

    allCorrect = True

    print("Tree:", rbt.traverse("color-print"))
    print("Deleting Black with Single Red Child 40\n")
    rbt.delete(40)
    print("Output:", rbt.traverse("color-print"), "\nExpected:","{17,black}, {8,red}, {5,black}, {15,black}, {25,red}, {18,black}, {80,black}" )

    if rbt.traverse("color-print") == "{17,black}, {8,red}, {5,black}, {15,black}, {25,red}, {18,black}, {80,black}":
        print("Deletion of 40, a Black node with Single Red Child is SUCCESS")
    else:
        print("Deletion of 40, a Black node with Single Red Child FAILED")
        allCorrect = False

    return allCorrect


def deleteTestBlackTwoRedChildren():
    print("\n------ Black with two Red Children Delete Test -------")
    rbt = RedBlackTree()
    ids = [8, 18, 5, 15, 17, 25, 40, 80, 35]
    tickets = generateFixedTickets(ids)
    for ticket in tickets:
        rbt.insert(ticket)

    allCorrect = True

    print("Tree:", rbt.traverse("color-print"))
    print("Deleting Black 40 with two Red Children\n")
    rbt.delete(40)
    print("Output:", rbt.traverse("color-print"), "\nExpected:","{17,black}, {8,red}, {5,black}, {15,black}, {25,red}, {18,black}, {80,black}, {35,red}" )

    if rbt.traverse("color-print") == "{17,black}, {8,red}, {5,black}, {15,black}, {25,red}, {18,black}, {80,black}, {35,red}":
        print("Deletion of 40, a Black node with two Red Children is SUCCESS")
    else:
        print("Deletion of 40, a Black node with two Red Children FAILED")
        allCorrect = False

    return allCorrect

def deleteTestRedwithTwoBlackChildren():
    print("\n------ Red with two Black Children Delete Test -------")
    rbt = RedBlackTree()
    ids = [8, 18, 5, 15, 17, 25, 40, 80]
    tickets = generateFixedTickets(ids)
    for ticket in tickets:
        rbt.insert(ticket)

    allCorrect = True

    print("Tree:", rbt.traverse("color-print"))
    print("Deleting Black 25 with two Red Children\n")
    rbt.delete(25)
    print("Output:", rbt.traverse("color-print"), "\nExpected:","{17,black}, {8,red}, {5,black}, {15,black}, {40,red}, {18,black}, {80,black}" )

    if rbt.traverse("color-print") == "{17,black}, {8,red}, {5,black}, {15,black}, {40,black}, {18,red}, {80,red}":
        print("Deletion of 25, a Red node with two Black Children is SUCCESS")
    else:
        print("Deletion of 25, a Red node with two Black Children FAILED")
        allCorrect = False

    return allCorrect

def deleteTestRootWithTwoRedChildren():
    print("\n------ Black with two Red Children Delete Test -------")
    rbt = RedBlackTree()
    ids = [8, 18, 5, 15, 17, 25, 40, 80, 35]
    tickets = generateFixedTickets(ids)
    for ticket in tickets:
        rbt.insert(ticket)

    allCorrect = True

    print("Tree:", rbt.traverse("color-print"))
    print("Deleting Root 17 with 2 red Children\n")
    rbt.delete(17)
    print("Output:", rbt.traverse("color-print"), "\nExpected:","{18,black}, {8,red}, {5,black}, {15,black}, {40,red}, {25,black}, {35,red}, {80,black}" )

    if rbt.traverse("color-print") == "{18,black}, {8,red}, {5,black}, {15,black}, {40,red}, {25,black}, {35,red}, {80,black}":
        print("Deletion of 17, a Black root with two Red Children is SUCCESS")
    else:
        print("Deletion of 17, a Black root with two Red Children FAILED")
        allCorrect = False

    return allCorrect

def deleteTestRootWithTwoRedChildren():
    print("\n------ Black with two Red Children Delete Test -------")
    rbt = RedBlackTree()
    ids = [8, 18, 5, 15, 17, 25, 40, 80, 35]
    tickets = generateFixedTickets(ids)
    for ticket in tickets:
        rbt.insert(ticket)

    allCorrect = True

    print("Tree:", rbt.traverse("color-print"))
    print("Deleting Root 17 with 2 red Children\n")
    rbt.delete(17)
    print("Output:", rbt.traverse("color-print"), "\nExpected:","{18,black}, {8,red}, {5,black}, {15,black}, {40,red}, {25,black}, {35,red}, {80,black}" )

    if rbt.traverse("color-print") == "{18,black}, {8,red}, {5,black}, {15,black}, {40,red}, {25,black}, {35,red}, {80,black}":
        print("Deletion of 17, a Black root with two Red Children is SUCCESS")
    else:
        print("Deletion of 17, a Black root with two Red Children FAILED")
        allCorrect = False

    return allCorrect

def deleteTestComplexOneICantCategorize():
    print("\n------ Complex Delete Test 1 -------")
    rbt = RedBlackTree()
    ids = [8, 18, 5, 15, 17, 25, 40, 80, 7]
    tickets = generateFixedTickets(ids)
    for ticket in tickets:
        rbt.insert(ticket)

    allCorrect = True

    print("Tree:", rbt.traverse("color-print"))
    print("Deleting 8\n")
    rbt.delete(8)
    print("Output:", rbt.traverse("color-print"), "\nExpected:","{17,black}, {7,red}, {5,black}, {15,black}, {25,red}, {18,black}, {40,black}, {80,red}" )

    if rbt.traverse("color-print") == "{17,black}, {7,red}, {5,black}, {15,black}, {25,red}, {18,black}, {40,black}, {80,red}":
        print("Deletion of 8 SUCCESS")
    else:
        print("Deletion of 8 FAILED")
        allCorrect = False

    return allCorrect

def deleteTestComplexOneICantCategorize2():
    print("\n------ Complex Delete Test 2 -------")
    rbt = RedBlackTree()
    ids = [8, 18, 5, 15, 16, 25, 40, 80, 7, 17, 19]
    tickets = generateFixedTickets(ids)
    for ticket in tickets:
        rbt.insert(ticket)

    allCorrect = True


    rbt.delete(8)
    rbt.delete(5)
    rbt.delete(15)
    print("Tree:", rbt.traverse("color-print"))
    print("Deleting 7\n")
    rbt.delete(7)
    print("Output:", rbt.traverse("color-print"), "\nExpected:","{25,black}, {18,red}, {16,black}, {17,red}, {19,black}, {40,black}, {80,red}" )

    if rbt.traverse("color-print") == "{25,black}, {18,red}, {16,black}, {17,red}, {19,black}, {40,black}, {80,red}":
        print("Deletion of 8 SUCCESS")
    else:
        print("Deletion of 8 FAILED")
        allCorrect = False

    return allCorrect


def deleteTestComplexOneICantCategorize3():
    print("\n------ Complex Delete Test 3 -------")
    rbt = RedBlackTree()
    ids = [8, 18, 5, 15, 17, 25, 40, 80, 7]
    tickets = generateFixedTickets(ids)
    for ticket in tickets:
        rbt.insert(ticket)

    allCorrect = True

    print("Tree:", rbt.traverse("color-print"))
    print("Deleting 15\n")
    rbt.delete(15)
    print("Output:", rbt.traverse("color-print"), "\nExpected:","{17,black}, {7,red}, {5,black}, {8,black}, {25,red}, {18,black}, {40,black}, {80,red}" )

    if rbt.traverse("color-print") == "{17,black}, {7,red}, {5,black}, {8,black}, {25,red}, {18,black}, {40,black}, {80,red}":
        print("Deletion of 15 SUCCESS")
    else:
        print("Deletion of 15 FAILED")
        allCorrect = False

    return allCorrect

def allOfTheseDeleteTests():
    allGood = 0
    deleteTestRedLeaf()
    deleteTestRedSingle()
    deleteTestBlackTwoRedChildren()
    deleteTestRedwithTwoBlackChildren()
    deleteTestRootWithTwoRedChildren()
    deleteTestComplexOneICantCategorize()
    deleteTestComplexOneICantCategorize2()
    deleteTestComplexOneICantCategorize3()


if __name__ == '__main__':
    basicInsertTest()
    biggerInsertTest2()
    stepByStepInsertion()
    allOfTheseDeleteTests()
