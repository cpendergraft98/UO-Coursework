'''
CIS 210 Project 4-1 Test Functions

Author: Cole Pendergraft
Credits: None

Write a function that enables testing and debugging of sscount0 and sscount1
from P34.
'''

def test_sscount(f, args, expected_result):
    '''
    (function, string, int) -> String (compares function output to expected output)
    
    This function tests the sscount1 and sscount0 functions and their outputs,
    and then compares their actual output with the expected output for the 
    function.
    
    >>> test_sscount(sscount1, 'sses assesses', 2)
    Testing sscount1
    Checking sses assesses
    The expected value of 2 is correct!
    
    >>> test_sscount(sscount0, 'fl flim flam fly fluke', 5)
    Testing sscount0
    Checking fl flim flam fly fluke
    Result of 4 does not match expected result of 5
    
    >>> test_sscount(sscount1, '', 0)
    Testing sscount1
    Checking an empty argument
    The expected value of 0 is correct!
    
    >>> test_sscount(sscount0, ' a', 0)
    Testing sscount0
    Checking  a
    The expected value of 0 is correct!
    '''
    args_list = str.split(args)
    #separates the args variable into separate inputs for the sscount1 or
    #sscount0 functions which both require two arguments.
    
    if len(args_list) < 1:
        print('Testing', str(f.__name__))
        print('Checking an empty argument')
        if expected_result == 0:
            print('The expected value of 0 is correct!')
        elif expected_result != 0:
            print('The expected result of', expected_result, 'does not match the actual value 0')
    #This if statement is important because it accounts for just having whitespace
    #in your argument, with at least one character aside from whitespace this code
    #will not execute. Any argument that only has whitespace should always output
    #to 0.
        
    else:
        needle = args_list[0]
        #The needle value should always come first in the args variable so we
        #can define it this way.
        
        args_list.remove(args_list[0])
        #We dont want to look at the needle value when counting repeated substrings
        #in the next part.
            
        haystack = ''
        
        for i in args_list:
            haystack = haystack + i    
        #for loop enables the user to calculate for inputs that have more than one
        #block of whitespace. For example, find fl in flim flam will work now, 
        #without needing to amend it to read find fl in flimflam.
    
        print('Testing', str(f.__name__))
        print('Checking', args)
        result = f(needle, haystack)
        
        if result == expected_result:
            print('The expected value of', expected_result, 'is correct!')
            #in order to make the program silent when a correct result is found,
            #all that must be done is remove the above line of code
            #and move the two print statements above into the elif statement
            #below, this way nothing prints for correct expected values.
            
        elif result != expected_result:
            print('Result of', result, 'does not match expected result of', expected_result)
        
    return None

def main():
    '''
    Executes the test_sscount function a set number of times with hardcoded variables
    in order to show the efficacy of test_sscount without needing to run the 
    function by hand multiple times. Returns nothing.
    '''
    test_sscount(sscount0, 'sses assesses', 2)
    print() #Blank spaces included for readability
    test_sscount(sscount1, 'sses assesses', 2)
    print()
    test_sscount(sscount0, 'an trans-panamanian banana', 6)
    print()
    test_sscount(sscount1, 'an trans-panamanian banana', 6)
    print()
    test_sscount(sscount0, 'needle haystack', 0)
    print()
    test_sscount(sscount1, 'needle haystack', 0)
    print()
    test_sscount(sscount0, '!!! !!!!!', 3)
    print()
    test_sscount(sscount1, '!!! !!!!!', 3)
    print()
    test_sscount(sscount0, 'o pneumonoultramicroscopicsilicovolcanoconiosis', 9)
    print()
    test_sscount(sscount1, 'o pneumonoultramicroscopicsilicovolcanoconiosis', 9)
    print()
    test_sscount(sscount0, ' ', 0)
    print()
    test_sscount(sscount1, ' ', 0)
    print()
    test_sscount(sscount0, 'a ', 0)
    print()
    test_sscount(sscount1, 'a ', 0)
    print()
    test_sscount(sscount0, ' abc', 0)
    print()
    test_sscount(sscount1, ' abc', 0)
    print()
    test_sscount(sscount0, 'a a', 1)
    print()
    test_sscount(sscount1, 'a a', 1)
    return None

#Functions imported from P34
    
def sscount0(needle, haystack):
    '''
    (string, string) -> int
    
    Counts the number of times a specific substring appears in a larger string
    and prints that counted value. Does not use string methods.
    
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
    
    #I had to adjust this function so that it returns the number of times the
    #substring appears rather than returning nothing, otherwise the test_sscount
    #function would not work.          
    #print(count)
    return count


def sscount1(needle, haystack):
    '''
    (string, string) -> int
    
    Uses string methods to produce the number of times a specific substring 
    appears in a larger string.
    
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
    
    #I had to adjust this function so that it returns the number of times the
    #substring appears rather than returning nothing, otherwise the test_sscount
    #function would not work.       
    #print(count)
    return count

main()