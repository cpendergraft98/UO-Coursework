"""
CIS 211 Lab 2

AUTHOR: Cole Pendergraft
"""

class Phone:

    def __init__(self, name: str):  #Always have self parameter in __init__
        self.name = name  #This is a class variable, it exists in the scope of the class

    def pickUp(self):
        print(f"Picking up: {self.name}")

    def dial(self, num: str):
        print(f"Dialing: {num}")

    def speak(self, msg: str):
        print(f"Speaking: {msg}")

    def call(self, num: str, msg: str):
        self.pickUp()
        self.dial(num)
        self.speak(msg)

#Syntax for subclasses:
#class [SubClassName].([SuperClassName)]
class SmartPhone(Phone):

    def __init__(self, name: str):
        super().__init__(name)
        #Why do we write it like this?
        #Save time, prevent yourself from having to copy down code from the
        #__init__ method of the SuperClass. DRY: Don't Repeat Yourself

    def openPhoneApp(self):
        print(f"Opening Phone App on: {self.name}")

    #Overriding: redefining a SuperClass method to act in a different way
    #when used in a subclass
    def call(self, num: str, msg: str):
        self.openPhoneApp()
        self.dial(num)
        self.speak(msg)

def main():
    ph1 = Phone('Panasonic')
    ph2 = Phone("AT&T")
    sPh1 = SmartPhone('iPhone')
    sPh2 = SmartPhone("Google")
    phoneList = [ph1, ph2, sPh1, sPh2]
    for phone in phoneList:
        phone.call("123-456-7890", "This is CIS 211 Lab")
        print("_____________________________________________")


if __name__ == '__main__':
    main()
    # creating a phone object
    #p1 = Phone("Catrick") #tabbed out because no longer necessary

    # calling a method on the object
    #p1.pickUp() #tabbed out bc no longer necessary

    # DON'T DO THE FOLLOWING:
    # Phone.pickup()

    #p1.dial("1234") #code no longer necessary
    #p1.speak("meow") #code no longer necessary
    #p1.call("123-456-7890", "meow") #tabbed out bc no longer necessary

    #sm1 = SmartPhone("Joe Exotic") #tabbed out bc no longer necessary
    #sm1.call("123-4567-890", "Hello") #tabbed out bc no longer necessary