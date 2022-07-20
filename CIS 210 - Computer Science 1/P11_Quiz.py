'''
CIS 210 Project 1-1 Prior Coding Experience Quiz
[Author]: Cole Pendergraft
[Credits]: N/A
Add docstrings to explain functions
'''

def q1(onTime, absent):
    '''
    (boolean, boolean) -> string
    Returns different strings depending on the True/False combinations of
    the boolean operators onTime and absent.
    
    >>> onTime = False, absent = True
    returns 'Is anyone there?'
    
    >>> onTime = False, absent = False
    returns 'Better late than never'
    
    >>>onTime = True, absent = True
    returns an error, cannot be both on time and absent
    '''
    if onTime:
        return('Hello!')
    elif absent:
        return('Is anyone there?')
    else:
        return('Better late than never.')

def q2(age, salary):
    ''' 
    (int, int) -> boolean
    Returns true or false depending on the integer associated with age 
    and salary
    
    >>> age =17, salary = 11000
    returns false
    
    >>> age = 17, salary = 9000
    returns true
    '''
    return (age < 18) and (salary < 10000)

def q3():
    '''
    (integer, integer) -> integer
    Compares two integers p and q and returns either 4, 5, or 6 depending on how 
    the integers compare, if p>q and q>4
    
    >>>p = 1, q = 4
    returns 6
    
    >>>p = 3, q = 1
    returns 4
    
    >>>p = 1, q = 6
    returns 5
    '''
    p = 1
    q = 2
    result = 4
    if p < q:
        if q > 4:
            result = 5
        else:
            result = 6

    return result

def q4(balance, deposit):
    '''
    (integer, integer) -> integer
    Combines two values balance and deposit and redefines the
    balance value on repeat until a counter reaches
    10, and then returns the updated balance.
     
    >>>balance = 1, deposit = 10
    returns 101
    
    >>>balance = 10, deposit = 1
    returns 20
    '''
    count = 0
    while count < 10:
        balance = balance + deposit
        count += 1

    return balance

def q5(nums):
    '''
    (list of numbers) -> integer
    Returns the number of integers greater than or equal 
    to 0 inside a list of numbers.

    >>> q5([0, 1, 2, 3, 4, 5])
    6
    >>> q5([0, -1, 2, -3, 4, -5])
    3
    '''
    result = 0
    i = 0
    while i < len(nums):
        if nums[i] >= 0:
            result += 1

        i += 1

    return result

def q6():
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
    while i < 4:
        p = p * 2
        i += 1

    return p
print(q6())