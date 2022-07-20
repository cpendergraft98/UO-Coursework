'''
CIS Project 3-3 Show Monte Pi

Author: Cole Pendergraft
Credits: None

Write a function that makes use of turtle to graphically display the outcome
of a Monte Carlo algorithm that approximates pi
'''
import math
import random
from turtle import *

def is_in_circle(x, y, r):
    '''
    (int, int, int) -> boolean
    
    The is_in_circle function keeps track of all of the points that fall
    within our inscribed function and those that fall outside of it by comparing
    the radius we have defined to the radius produced given our values for 
    x and y.
    
    >>> is_in_circle(2,2,1)
    False
    
    >>> is_in_circle(0.5, 0.5, 1)
    true
    '''
    
    return(math.sqrt(x**2 + y**2) <= r)
    
def reportPi(numDarts, approximate_pi):
    '''
    (int, int) -> int
    
    The reportPi function compares the user-generated approsimation for pi
    to the actual math.pi value and computes a percentage error so we can see
    how close our approximation is. Returns nothing.
    
    >>> reportPi(20, 3.2)
    After 20 iterations, the approximate value for pi is 3.2
    The math.pi value for pi is 3.141592653589793
    This is off of the actual value for pi by 1.8591635788130243 percent
    
    >>> reportPi(10, 3.2)
    After 10 iterations, the approximate value for pi is 3.2
    The math.pi value for pi is 3.141592653589793
    This is off of the actual value for pi by 1.8591635788130243 percent
    '''
    error = round(abs(((math.pi - approximate_pi)/math.pi)*100), 3)
    print('After', numDarts, 'iterations, the approximate value for pi is', approximate_pi)
    print('The math.pi value for pi is', math.pi)
    print('This approximation is off of the actual value for pi by', error, 'percent')
    
    return None

def showMontePi(numDarts):
    '''
    (int) -> graphic, integer
    
    CALLS: is_in_circle, drawboard
    
    This function makes use of the Monte Carlo method to create an algorithm
    that relies on random number generation and the placement of dots within
    a circle that is inscribed in a square to produce an approximation for pi
    that gets more accurate with more iterations. It returns the approximate
    value for pi.
    
    It then also creates a turtle graphic that displays the distribution of
    points, with the ones outside the circle in red and those inside in blue.
    
    It should be noted that because the Monte Carlo method relies on random
    number generation, every input for NumDarts can have varying outputs
    depending what numbers were generated for x and y. Essentially, inputting
    a value like 20 into the function won't approximate to 3.4 every time.
    
    >>> showMontePi(20)
    3.4 
    graphic
    
    >>> showMontePi(10)
    3.2
    graphic
    '''
    
    drawboard()
     
    inCircle = 0

    for i in range(numDarts):
        x = random.random()
        y = random.random()
        r = 1

        #d = math.sqrt(x**2 + y**2)

        # show the dart on the board
        if is_in_circle(x,y,r) == True:
            inCircle += 1
            color('blue')
        else:
            color('red')

        goto(x, y)
        dot()

    # calculate approximate pi
    approxPi = inCircle/numDarts * 4

    exitonclick()

    return approxPi

def drawboard():
    '''
    (null) -> graphic
    
    The drawboard function makes use of Turtle in order to draw the x and y
    axes of the graph that will then be used to display the distribution of
    ponts. It also zooms into the first quadrant of the graph so that we are
    only worrying about positive values.
    '''
    clearscreen()
    Screen()
    setworldcoordinates(0, 0, 2, 2)

    speed('fastest'); hideturtle()
    penup()

    goto(-1, 0)
    pendown()
    goto(1, 0)
    penup()
    goto(0, 1)
    pendown()
    goto(0, -1)
    penup()
    goto(0, -1)
    

    
    return None

def main():
    '''
    (null) -> int, string, graphic
    
    The main funtion wraps up the drawboard, is_in_circle, reportPi, and 
    showMontePi functions all into one nice, neat package.
    
    >>> main()
    graphic
    After 100 iterations, the approximate value for pi is 3.04
    The math.pi value for pi is 3.141592653589793
    This approximation is off of the actual value for pi by 
    3.234 percent
    '''
    reportPi(100, showMontePi(100))
    
    return None

main()
