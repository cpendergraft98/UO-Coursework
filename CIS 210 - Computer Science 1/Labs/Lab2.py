# -*- coding: utf-8 -*-
"""
CIS 210 Lab 2

Author: Cole Pendergraft
Credits: None
"""

def is_even(n):
    '''
    (int) -> boolean
    
    Returns True if n is an even number
    
    >>>is_even(100)
    true
    
    >>>is_even(101)
    false
    '''
    return (n % 2) == 0
print(is_even(2))
result = is_even(3)


def welcome():
    '''
    () -> ()
    
    Print welcome message.
    
    >>> welcome()
    Good morning, CIS 210!
    '''
    
    print('Good morning, CIS 210!')
    return None

welcome()

def est_tax(income, exemptions):
    '''
    (number, integer) -> float
    
    Generates an estimate for federal income tax.
    Prints result.
    Example from class, revised to prnt rather than return estimated tax.
    
    calls: taxable
    
    >>>est_tax(20000, 1)
    1870.0
    '''
    #set values needed to generate estimate
    std_exempt = 4150 
    std_deduct = 6500
    tax_rate = .20
    
    #calculate federal tax by adjusting reporte income and applying tax rate.
    taxable_income = taxable(income, exemptions, std_exempt, std_deduct)
    estimated_tax = taxable_income * tax_rate
    
    print('Estimated tax is:', estimated_tax)
    return None


def taxable(income, exemptions, std_exempt, std_deduct):
    '''
    (number, int, number, number) -> float
    Adjust gross income (i) to taxable income by applying 
    standard deduction and exemptions.
    
    called by: est_tax
    
    >>>taxable(20000, 1, 4150, 6500)
    9350
    '''
    taxable_income = income - std_deduct
    exempt_adjust = std_exempt * exemptions
    taxable_income = taxable_income - exempt_adjust
    
    print(taxable_income)
    return taxable_income

est_tax(20000, 1)