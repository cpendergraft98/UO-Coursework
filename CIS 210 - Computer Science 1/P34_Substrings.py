'''
CIS 210 Project 3-4 Substring Counter

Author: Cole Pendergraft
Credits: None

Calculates the number of times a specific substring appears in a given string.
'''
import doctest
def sscount0(needle, haystack):
    '''
    (string, string) -> int
    
    Counts the number of times a specific substring appears in a larger string
    and prints that counted value. Returns nothing.
    
    >>> sscount0('sses', 'assesses')
    2
    
    >>> sscount0('i', 'mississippi')
    4
    '''
    big = len(haystack)
    small = len(needle)
    count = 0
    
    for i in range((big-small)+1):
        if needle == (haystack[i:i+small]):
            count += 1
            
    print(count)
    return None

def sscount1(needle, haystack):
    '''
    (string, string) -> int
    
    Uses string methods to produce the number of times a specific substring 
    appears in a larger string. Returns nothing.
    
    >>> sscount1('ss', 'mississippi')
    2
    
    >>> sscount1('ack', 'jack black')
    2
    '''
    big = len(haystack)
    small = len(needle)
    count = 0
    
    for i in range((big - small)+1):
        if haystack.startswith(needle, i , i+small):
            count += 1
            
    print(count)
    return None

print(doctest.testmod())