from mealticket import *
from cpenderg_lab2 import *


def main():
    #Step-01: Build a new priority queue and generate some mealtickets
    queue1 = PriorityQueue(8)
    tickets = generateMealTickets(8)

    #STEP-02: Print result of isEmpty()/full()
    print("=== Testing Queue ===")
    print("Test 1: Queue Empty/Full")
    print("Result: ", queue1.isEmpty(), " - ", queue1.isFull())
    print()

    #Step-03: Push tickets into Queue
    print("Test 2: Inserting tickets until full.")
    for ticket in tickets:
        print("Result: ", queue1.enqueue(ticket))
    print()

    #STEP-04: Print queue at the top/empty Full
    print("Test 3: Queue __str__ and Empty/Full")
    print("Result: ", queue1.isEmpty(), " - ", queue1.isFull())
    print(queue1)
    print()

    #Step-05: Print max, print Queue, extract max, repeat first 2
    print("Test 3: Extracting highest priority ticket")
    print("Displaying current highest priority ticket:")
    queue1.peekMax().display()
    print("Extracting Max: ", queue1.dequeueMax() != False)
    print(queue1)
    print("Displaying current highest priority ticket:")
    queue1.peekMax().display()
    print("==== End Testing ====")
    print("\n")


main()
