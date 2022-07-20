'''
CIS 210 Project 2-3 Turtle Graphics Flower

A program that will draw a 'Flower' composed of x squares with side length y.

Author: Cole Pendergraft
Credits: Python Progamming in Context by Bradley N. Miller and David L. Ranum,
used to generate drawSquare function.
'''
from turtle import *

def drawSquare(length_side):
    '''
    (int) -> graphic
    
    This program takes an integer input for sidelength and creates a square 
    with sides of that length
    
    >>>drawSquare(50)
    draws a square of side length 50 units
    returns nothing
    
    >>>drawSquare(100)
    draws a square of side length 100 units
    returns nothing
    '''
    for i in range(4):
        forward(length_side)
        right(90)
    return None

def drawFlower(num_squares, length_side):
    '''
    (int, int) -> graphic
    
    Draws a 'flower' based on the length of the side of one square(a petal) and
    the number of squares used to draw
    CALLS: drawSquare
    
    >>>drawFlower(10,50)
    draws a flower made up of 10 squares with side lengths of 50 units
    returns nothing
    
    >>drawflower(3, 100)
    draws a flower made up of 3 squares with side lengths of 100 units
    returns nothing
    '''
    dtheta=360/num_squares
    clearscreen()
    speed(8000)
    for i in range(num_squares):
        rt(dtheta)
        drawSquare(length_side)
    setheading(270)
    fd(length_side*4)
    return None

def drawPolygon(number_sides, length_side):
    '''
    (int, int) -> graphic
    
    This function takes x number of sides of side length y and produces a polygon
    with matching values.
    
    >>>drawPolygon(8, 40)
    draws an Octagon with sides of length 40 units
    returns nothing
    
    >>>drawPolygon(4, 90)
    draws a Square with side lengths of 90 units
    returns nothing
    '''
    dtheta = 360/number_sides
    for i in range(number_sides):
        fd(length_side)
        rt(dtheta)
        
    return None

def main():
    '''
    Wraps up the drawPolygon and drawFlower functions into one callable
    function
    '''
    drawFlower(50,50)
    penup()
    setpos(0, 200)
    pendown()
    drawPolygon(8,50)
    
    return None

main()

