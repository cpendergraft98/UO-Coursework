'''
CIS 210 Project 2-1 Netpay Function
Author: Cole Pendergraft
Credits: None

This code computes the total income one receives after tax based on the
number of hours worked.
'''

def tax(gross_pay):
    '''
    (float) -> float
    This part of the function computes just the tax on a specific
    income called gross_pay. This function returns the tax on a specific 
    income.
    
    >>>tax(1)
    returns .15
    
    >>>tax(40)
    returns 6.0
    
    '''
    tax = gross_pay * .15
    return tax

def netpay(hours):
    '''
    (int) -> float
    This function first calculates the untaxed income one would receive based
    on hours worked, and then takes the tax computed with the tax function 
    and calculates the total income after the tax is removed from the untaxed
    income. This function returns the taxed income.
    
    >>>netpay(1)
    returns 9.5625
    
    >>>netpay(40)
    returns 382.5
    '''
    untaxed = 11.25 * hours
    taxed = untaxed - tax(untaxed)
    return taxed

def main(hours):
    '''
    (float) -> string, float
    This function simply takes the computed taxed income from the netpay
    function and and prints it out in a cleaner, more readable manner. 
    This function returns nothing, but it prints out a statement that depends 
    on the returned value for taxed income.
    
    >>>main(1)
    prints 'For 1 hour(s) of work the net income is 9.5625'
    returns nothing
    
    >>>main(40)
    prints 'For 40 hour(s) of work the net income is 382.5'
    returns nothing
    '''
    netpay(hours)
    print("For", hours, "hour(s) work the net income is",netpay(hours))
    return None

main(1)