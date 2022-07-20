"""
Author: Jared Hall
Description: A simple meal ticket program.
Date: 01/14/2020
Notes:
    1. This program contains the meal ticket class.
"""
#------------------------------ Classes ----------------------------------------
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
        """ Add an Item to the MealTicket """
        self.items.append(item)
        self.totalCost += item[1]
        return True

    def display(self):
        """Print out the MealTicket """
        print("=== Displaying Ticket ===")
        print("Ticket Name: ", self.TicketName)
        print("Ticket ID: ", self.ticketID)
        print("Total Cost: ", round(self.totalCost, 2))
        print("Ticket Items: ")
        for i in range(0, len(self.items)):
            msg = "  Item name: " + str(self.items[i][0])
            msg += " -- Item cost: " + str(self.items[i][1])
            print(msg)
        print("========== End ==========\n")
#-------------------------------------------------------------------------------

#------------------------- Pre-Made Tickets ------------------------------------
#Feel free to add your own interesting meals here! (f^.^) f
ticket1 = MealTicket("Jared's Breakfast")
ticket1.addItem(("Eggs", 4.50))
ticket1.addItem(("Bacon", 2.50))
ticket1.addItem(("OJ", 1.00))
ticket2 = MealTicket("Jared's Lunch")
ticket2.addItem(("Steak", 14.99))
ticket2.addItem(("Salad", 3.00))
ticket2.addItem(("Lychee", 0.50))
ticket3 = MealTicket("Jared's Dinner")
ticket3.addItem(("Noodles", 11.50))
ticket3.addItem(("Dumplings", 5.99))
ticket3.addItem(("Whiskey", 19.99))
ticket4 = MealTicket("Jared's Snacks")
ticket4.addItem(("Dragon Fruit", 8.50))
ticket4.addItem(("Strawberry", 3.25))
ticket4.addItem(("Passion Fruit", 4.50))
#-------------------------------------------------------------------------------

#---------------------------- Simple Testing main ------------------------------
if(__name__ == "__main__"):
    def main():
        print(" === Testing MealTicket class ===")

        #Step-03: Display tickets
        ticket1.display()
        ticket2.display()
        ticket3.display()
        ticket4.display()

        return True
    main()
#-------------------------------------------------------------------------------
