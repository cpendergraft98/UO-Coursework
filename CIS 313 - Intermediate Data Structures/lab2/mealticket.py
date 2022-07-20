"""
Author: Jared Hall
Description: A simple meal ticket program.
Date: 01/14/2020
Notes:
	1. This program contains the meal ticket class
	   developed in the video tutorial.
"""
from random import uniform, shuffle, randint

class MealTicket():
	""" A simple meal ticket class. """
	ID = 1

	def __init__(self, ticketName):
		""" Constructor for the meal ticket class """
		self.TicketName = ticketName
		self.ticketID = MealTicket.ID
		self.totalCost = 0
		self.items = []
		MealTicket.ID += 1

	def addItem(self, item):
		""" Adds items to the meal tickets """
		self.items.append(item)
		self.totalCost += item[1]
		self.totalCost =  round(self.totalCost, 2)
		return True

	def display(self):
		""" Displays the meal ticket nicely """
		print("=== Displaying Ticket ===")
		print("Ticket Name: ", self.TicketName)
		print("Ticket ID: ", self.ticketID)
		print("Total Cost: ", round(self.totalCost, 2))
		print("Ticket Items: ")
		for i in range(0, len(self.items)):
			print("	 Item name: ", self.items[i][0], end="")
			print(" -- Item cost: ", self.items[i][1])
		print("========== End ==========\n")
import pprint
#added a function that outputs an array of mealtickets so we gots mo data
def generateMealTickets(size):
	""" Generates an array of mealtickets based on the integer <size> """
	mealtickets = []
	for i in range(size):
		ticket = MealTicket("Jared's Meal " + str(i))
		ticket.ticketID = randint(1, size)
		ticket.addItem(("Item 1", round(uniform(0, 30), 2)))
		ticket.addItem(("Item 2", round(uniform(0, 30), 2)))
		ticket.addItem(("Item 3", round(uniform(0, 30), 2)))
		mealtickets.append(ticket)
	return mealtickets


if(__name__ == "__main__"):
	def main():
		print(" === Testing MealTicket class ===")
		tickets = generateMealTickets(10)
		for t in tickets:
			t.display()

		return True
	main()
