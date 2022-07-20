'''
CIS 210 Project 3-2 Approximating Pi

Author: Cole Pendergraft
Credits: None

Use the Monte Carlo method to produce an approximation for pi without importing
math.
'''
import random
import math

def montePi(numDarts):
    '''
    (int) -> int
    
    CALLS: is_in_circle
    
    This function makes use of the Monte Carlo method to create an algorithm
    that relies on random number generation and the placement of dots within
    a circle that is inscribed in a square to produce an approximation for pi
    that gets more accurate with more iterations. It returns the approximate
    value for pi.
    
    It should be noted that because the Monte Carlo method relies on random
    number generation, every input for NumDarts can have varying outputs
    depending what numbers were generated for x and y. Essentially, inputting
    a value like 20 into the function won't approximate to 3.4 every time.
    
    >>> montePi(20)
    3.4 
    
    >>> montePi(10)
    3.2
    '''
    inCircle = 0
    r = 1
    
    for i in range(numDarts):
        x = random.random()
        y = random.random()
        #d = math.sqrt(x**2 + y**2) Not needed because we say r=1
        r = 1
        
        if is_in_circle(x, y, r) == True:
            inCircle += 1
            
    approximate_pi = (inCircle/numDarts) * 4
    
    return approximate_pi

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

def main():
    '''
    (null) -> string, int
    
    The main function wraps up reportPi, montePi, and is_in_circle into one,
    nice, neat, and callable function.
    
    >>> main()
    After 10 iterations, the approximate value for pi is 3.6
    The math.pi value for pi is 3.141592653589793
    This approximation is off of the actual value for pi by 14.592 percent

    After 10000 iterations, the approximate value for pi is 3.1672
    The math.pi value for pi is 3.141592653589793
    This approximation is off of the actual value for pi by 0.815 percent

    After 10000000 iterations, the approximate value for pi is 3.1420312
    The math.pi value for pi is 3.141592653589793
    This approximation is off of the actual value for pi by 0.014 percent
    '''
    reportPi(10, montePi(10))
    print()
    reportPi(10000, montePi(10000))
    print()
    reportPi(10000000, montePi(10000000))
    
    return None
