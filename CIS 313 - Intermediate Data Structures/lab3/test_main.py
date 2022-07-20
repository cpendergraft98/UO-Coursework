from mealticket import *
from cpenderg_lab3 import *
from random import *


def defaultTestTickets(vals):
    """
        Generates a list of meal tickets with the provided list of values
    """
    result = []
    for i in range(len(vals)):
        ticket = MealTicket("My Meal " + str(i))
        ticket.ticketID = vals[i]
        ticket.addItem(("Test Item", round(uniform(0, 30), 2)))
        result.append(ticket)
    return result


def makeTestTickets(size):
    """
        Generates a list of random mealtickets with no duplicates
        Returns <size> mealtickets
    """
    result = []
    vals = sample(range(1, size+20), size)
    for i in range(size):
        ticket = MealTicket("My Meal " + str(i))
        ticket.ticketID = vals[i]
        ticket.addItem(("Test Item", round(uniform(0, 30), 2)))
        result.append(ticket)
    return result


if __name__ == '__main__':
    SIZE = 8                            # Number of nodes you want in tree
    testValues = [6, 7, 1, 5, 3, 4]     # Premade tickets

    testTickets = makeTestTickets(SIZE)               # For random tickets
    #testTickets = defaultTestTickets(testValues)    # For premade tickets

    testTree = BinarySearchTree()

    print("List of Tickets:", end=" ")
    print([t.ticketID for t in testTickets])

    print("============ Testing Insert Method ============")
    res = True
    for ticket in testTickets:
        res = testTree.insert(ticket)
        print("Inserting " + str(ticket.ticketID), end=": ")
        print(res)
        if not res:
            print("SOMETHING WENT WRONG")
            break

    if res:
        print("============ Testing Traversal Methods ============")
        print("Pre-order:", end=" ")
        print(testTree.traverse("pre-order"))
        print("In-order:", end=" ")
        print(testTree.traverse("in-order"))
        print("Post-order:", end=" ")
        print(testTree.traverse("post-order"))


    print("============ Testing Find Method ============")
    findTestVals = []
    for _ in range(2):
        # Grab a ticket that should be in the tree
        findTestVals.append(choice(testTickets).ticketID)
        # Grab a random value (may or may not be in tree)
        findTestVals.append(randint(1, SIZE+20))
    for value in findTestVals:
        result = testTree.find(value)
        if result is not False:
            result = True
        print(f"Is {value} in the tree: {result}" )

    print("============ Testing Delete Method ============")
    deleteID = choice(testTickets).ticketID
    print(f"Deleting node {deleteID}...")
    deleteResult = testTree.delete(deleteID)
    if deleteResult:
        print("DELETION SUCCESSFUL!\n")
        print("Updated Traversals")
        print("Pre-order:", end=" ")
        print(testTree.traverse("pre-order"))
        print("In-order:", end=" ")
        print(testTree.traverse("in-order"))
        print("Post-order:", end=" ")
        print(testTree.traverse("post-order"))
    else:
        print("DELETION FAILED!\n")
