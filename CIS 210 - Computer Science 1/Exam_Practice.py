from turtle import *

def drawshape(s, n):
    '''
    Draws an n sided polygon with side length
    s.

    Parameters
    ----------
    s : Length of one side of the polygon
    n : How many sides we want our polygon to 
    have

    Returns
    -------
    None.

    '''
    turn = 360/n
    for i in range(n):
        fd(s)
        lt(turn)
        
    exitonclick()
        
    return None

drawshape(100, 9)