'''
CIS 210 Project 2-2 Square Root Approximator

Author: Cole Pendergraft
Credits: None
'''
import math
def mysqrt(n, k):
    '''
    (int, int) -> float
    This function uses the Babylonian method to apporoximate the square root
    of a number n over a number of iterations k.
    
    >>>mysqrt(25, 5)
    returns 5.000023178253949
    
    >>> mysqrt(25, 10)
    returns 5.0
    '''
    x_initial = 1
    x_next = 0
    for i in range(k):
        x_next = 0.5*(x_initial + (n/x_initial))
        x_initial = x_next
    
    return x_next

def sqrtcompare(num, iterations):
    '''
    (int, int) -> float, string
    
    CALLS: mysqrt(n, k)
    
    This function calls mysqrt(n, k) and compares the approximated square root
    to the actual square root and provides a percentage error that depicts
    how far off the approximation is. The function doesn't return anything.
    
    >>>sqrtcompare(10000, 8)
    User-generated squareroot is 101.20218365353946
    Mathematical squareroot is 100.0
    This is a percentage error of 1.2
    returns nothing
    
    >>>sqrtcompare(100, 5)
    User-generated squareroot is 10.032578510960604
    Mathematical squareroot is 10.0
    This is a percentage error of 0.33
    returns nothing
    '''
    my_sqrt = mysqrt(num, iterations)
    real_sqrt = math.sqrt(num)
    percentage_error = round(abs(((abs(real_sqrt)-my_sqrt)/real_sqrt)*100), 2)
    print('User-generated squareroot is', my_sqrt)
    print('Mathematical squareroot is', real_sqrt)
    print('This is a percentage error of', percentage_error)
    
    return None

def main(num, iterations):
    '''
    (int, int) -> float, string
    CALLS: mysqrt, sqrtcompare
    
    This function incorporates the mysqrt and sqrtcompare functions and 
    wraps them up in a nice, neat package. Returns nothing.
    
    >>>main(10000,8)
    User-generated squareroot is 101.20218365353946
    Mathematical squareroot is 100.0
    This is a percentage error of 1.2
    returns nothing
    
    >>>main(100, 5)
    User-generated squareroot is 10.032578510960604
    Mathematical squareroot is 10.0
    This is a percentage error of 0.33
    returns nothing
    '''
    sqrtcompare(num, iterations)
    return None

main(100, 5)