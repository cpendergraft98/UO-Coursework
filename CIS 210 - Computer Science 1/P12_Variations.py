# -*- coding: utf-8 -*-
"""
CIS 210 Project 1-2 Python Variations
[Author]: Cole Pendergraft
[Credits]: N/A
Write functions that manipulate integers in a variety of ways.
"""

def convert(i, j, k):
    '''
    (int, int, int) -> int
    Converts a list of indiviudal numbers of the form [i, j, k]
    into a single combined integer of the formn kji.
    
    >>>convert(3, 2, 1)
    returns 123
    
    >>>conver(4, 7, 3)
    returs 374
    '''
    num_list = [i, j, k]
    return 100*num_list[2] + 10*num_list[1] + num_list[0]
    
print(convert(1, 2, 3))

def add_list(n):
    '''
    (int) -> float
    Adds up the individual digits in a 3-digit integer
    
    >>>add_list(789)
    returns 24
    
    >>>add_list(321)
    returns 6
    '''
    a = n % 10
    a -= n % 1
    a /= 1
    b = n % 100
    b -= (n % 10)
    b /= 10
    c = n % 1000
    c -= n % 100
    c /= 100
    
    return a+b+c
print(add_list(789))

def add_list2(n):
    '''
    (int) -> float
    Adds up the individual digits of an integer of any length
    
    >>>add_list2(10205)
    returns 8
    
    >>>add_list2(82)
    returns 10
    '''
    num_list = []
    j = 10
    k = 1
    while n/j > 0.09:
       value = ((n % j) - (n % k))/k
       num_list.append(value)
       j *= 10
       k *= 10
           
    return sum(num_list)
     
print(add_list2(91140749))