"""
Author: Jared Hall, <your_name_here>
Description: A simple meal ticket program.
Date: 01/10/2020 -- Last Modified: <date>
Notes:
    1. This is a sample testing main for lab 1.
	2. I test the most obvious corner cases here. You will need to account
	   for the rest. Give it some thought and use the methodology
	   discussed in Lab.
	3. <Additional points you think I should consider when grading your codes.>
"""
from mealticket import *
from cpenderg_lab1 import *
#Add an import statement for your classes here.

def main():
	#PART 1: Queues
	#Step-01: Build a new queue.
	queue1 = Queue(4)

	#STEP-02: Print result of isEmpty()/full()
	print("=== Testing Queue ===")
	print("Test 1: Queue Empty/Full")
	print("Result: ", queue1.isEmpty(), " - ", queue1.isFull())
	print()

	#Step-03: Push tickets into Queue
	print("Test 2: Enqueueing tickets until full.")
	print("Result: ", queue1.enqueue(ticket1))
	print("Result: ", queue1.enqueue(ticket2))
	print("Result: ", queue1.enqueue(ticket3))
	print("Result: ", queue1.enqueue(ticket4))
	print("Result: ", queue1.enqueue(ticket1))
	print()

	#STEP-04: Peak at the top/empty Full
	print("Test 3: Queue front and Empty/Full")
	print("Result: ", queue1.isEmpty(), " - ", queue1.isFull())
	temp = queue1.front()
	print("The ticket at the front of the queue is: ", temp.ticketID)
	print()

	#Step-05: Dequeue and print
	print("Test 3: dequeueing tickets until empty.")
	temp = queue1.dequeue()
	temp.display()
	temp = queue1.dequeue()
	temp.display()
	temp = queue1.dequeue()
	temp.display()
	temp = queue1.dequeue()
	temp.display()
	temp = queue1.dequeue()
	if(temp == False):
		print("Queue Empty: Dequeue Failed")
	else:
		print("Something went wrong here...")

	print("Queue empty/full result: ", queue1.isEmpty(), " - ", queue1.isFull())
	print("==== End Testing ====")
	print("\n")

	#Part 2: Stack
	#Step-01: Build a new stack
	stack1 = Stack(4)

	#Step-02: print isEmpty/full
	print("=== Testing Stack ===")
	print("Test 1: Stack Empty/Full")
	print("Result: ", stack1.isEmpty(), " - ", stack1.isFull())
	print()

	#Step-03: Push tickets into Stack
	print("Test 2: Pushing tickets until full.")
	print("Result: ", stack1.push(ticket1))
	print("Result: ", stack1.push(ticket2))
	print("Result: ", stack1.push(ticket3))
	print("Result: ", stack1.push(ticket4))
	print("Result: ", stack1.push(ticket1))
	print()

	#STEP-04: Peak at the top/empty Full
	print("Test 3: Stack peak and Empty/Full")
	print("Result: ", stack1.isEmpty(), " - ", stack1.isFull())
	temp = stack1.peek()
	print("The ticket at the top of the stack is: ", temp.ticketID)
	print()

	#Step-05: pop and print
	temp = stack1.pop()
	temp.display()
	temp = stack1.pop()
	temp.display()
	temp = stack1.pop()
	temp.display()
	temp = stack1.pop()
	temp.display()
	temp = stack1.pop()
	if(temp == False):
		print("Stack Empty: Pop Failed")
	else:
		print("Something went wrong here...")
	print("Stack empty/full result: ", stack1.isEmpty(), " - ", stack1.isFull())

	return True
main()
