'''
CIS 210 Project 3-1 Fizzbuzz

Author: Cole Pendergraft
Credits: None

Write a function that iterates through numbers that increase by one and tests
whether they are divisible by 3, 5, or both
'''
def fizzbuzz(n):
    '''
    (int) -> int or string
    
    The fizzbuzz function takes all numbers starting from 1 to n and tests if
    they are divisible by 3 or 5. Numbers that are divisible by both 3 and 5
    print fizzbuzz, numbers only divisible by three print the string
    fizz, and numbers only divisible by 5 print the string buzz. If the number 
    is not divisible by either 3 or 5, then the number alone is printed. 
    The function returns nothing.
    
    >>> fizzbuzz(5)
    
    1
    2
    fizz
    4
    buzz
    Game over!
    
    >>> fizzbuzz(11)
    
    1
    2
    fizz
    4
    buzz
    fizz
    7
    8
    fizz
    buzz
    11
    Game over!
    '''
    counter = 1
    for i in range(n):
        divisible_by_3 = counter % 3
        divisible_by_5 = counter % 5
        if divisible_by_3 == 0 and divisible_by_5 == 0:
            print('fizzbuzz')
            counter += 1
        elif divisible_by_3 == 0:
            print('fizz')
            counter += 1
        elif divisible_by_5 == 0:
            print('buzz')
            counter += 1
        else:
            print(counter)
            counter += 1
    print("Game over!")
    return None
