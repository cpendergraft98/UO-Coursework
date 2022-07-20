'''
CIS 210 Project 2-0 For Loop Practice

Author: Cole Pendergraft
Credits: None
'''

def q6_better():
    '''
    (integer, integer) -> integer
    Changes the value of variable p based on the value of variable i.
    
    >>> i = 2, p = 1
    returns 4
    
    >>> i = 0, p = 1
    returns 16
    '''
    i = 0
    p = 1
    for i in range(4):
        p = p * 2
        i += 1

    return p

print(q6_better())

def q6_final(n, m):
    '''
    (int, int) -> int
    
    This function raises a number n to the power of some number m and returns
    the product.
    
    >>>q6_final(2,2)
    returns 4
    
    >>>q6_final(2, 1)
    returns 2
    '''
    value = n
    for i in range(m-1):
        value *= n
        
    return value

print(q6_final(2, 2))

def add_digits2a(n):
    '''
    (int) -> int
    This function adds together the digits of a 3-digit long number and
    returns that value.
    
    >>>add_digits2b(321)
    returns 6

    >>>add_digits(405)
    returns 9    
    '''
    num_list = []
    j = 10
    k = 1
    for i in range(3):
       value = ((n % j) - (n % k))/k
       num_list.append(value)
       j *= 10
       k *= 10
    return sum(num_list)

print(add_digits2a(405))

'''
It would be a very bad idea to replace the while loop in the add_digits2b
with a for loop because a for loop requires a known number of iterations, so 
using a for loop would prevent you from being able to add the digits of a 
number of x digits long unless you specified the length of your number
beforehand (like in the function above where we explictly say for i in 
range(3)). A while loop allows us to iterate the function up until a specific
point that doesn't need to be related to the length of the number.
'''