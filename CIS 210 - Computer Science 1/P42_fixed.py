'''
CIS 210 Project 4-2 Bug Fixing

Author: Cole Pendergraft
Credits: None

Fix bugs in the code below
'''

import doctest

def ratsBug(weight, rate):   #need more doctest examples
    '''(number, number) -> tuple

    Return number of weeks it will
    take for a rat to weigh 1.5 times
    as much as its original weight
    (weight > 0) if it gains at rate (rate > 0).

    >>> ratsBug(10, .1)     # normal
    (16.1, 5)
    >>> ratsBug(1, .5)      # edge - just one week
    (1.5, 1)
    
    #My examples follow
    
    >>> ratsBug(0, .1) #edge - a weight of 0
    (0, 0)
    
    >>> ratsBug(15, .05)
    (23.3, 9)
    
    >>> ratsBug(3, .4)
    (5.9, 2)
    '''
    weeks = 0
    upper_bound = weight * 1.5
    while weight < (upper_bound):
        #redefined the upper bound of the while loop so that it does not use the
        #newly updated weight value when doing weight * 1.5
        #added a colon to the above statement
        weight += (rate*weight)
        weeks = weeks + 1
        #changed wks variable to weeks
        
    weight = round(weight, 1)
    return (weight, weeks)

def countSeqBug(astr):   #need more doctest examples
    '''(str) -> int

    Returns the length of the longest recurring
    sequence in astr

    >>> countSeqBug('abccde')  # normal  	
    2
    >>> countSeqBug('')        # edge - empty string
    0
    
    #My examples follow
    >>> countSeqBug('abcdeee') #Repeated values at the end of string
    3
    
    >>> countSeqBug('abbcdddeffff') #Multiple repeated values
    4
    
    >>> countSeqBug('aabccdee') #Multiple repeated values of the same length
    2
    '''
    if len(astr) != 0:
        prev_item = astr[0]
        dup_ct = 1
        high_ct = 1
    else:
        high_ct = 0
        dup_ct = 0
        
    for i in range(1, len(astr)):
        if astr[i] == prev_item:
            dup_ct += 1
            
            if dup_ct > high_ct: #moved the if statement up here because its prettier
                high_ct = dup_ct
            
        else:
            prev_item = astr[i]
            dup_ct = 1
			#moved the dup_ct = 1 statement into the else statment
           

    return high_ct

def my_averageBug(dataset):   #need more doctest examples
    '''(str) -> float

    Returns average of values in input string values,
    but zeros do not count at all.  Return 0 if there
    is no real data.
    
    >>> my_averageBug('23')    #normal, no zeros
    2.5
    >>> my_averageBug('203')   #normal, a zero
    2.5
    >>> my_averageBug('0000')  #all zeros
    0
    >>> my_averageBug('1')     #single item string
    1.0
    >>> my_averageBug('05050505')  
    5.0
    
    #The following are examples that I wrote
    
    >>> my_averageBug('')      #blank input
    0
    
    >>> my_averageBug('2233')
    2.5
    
    >>> my_averageBug('34904')
    5.0
    '''
    
    count = 0
    total = 0
    for value in dataset:
        #print(value)
        if value != '0':
            total += int(value)
 # use int to change string to integer
            count += 1
            
        elif value == '0':
            pass
        #A big part of the initial error with this code was the lack of an elif
        #statement telling the code what to do if value == 0. It knows what to 
        #do when value != 0, but we hadn't instructed it to throw away values
        #that are equal to 0.
        
    if count != 0:
        avg = total / count
        #This is important because it prevents division by zero. Before, if we
        #had a dataset of all 0's, the count would come out to 0 and the 
        #output would be a zero division error. Now we have expressly told the
        #machine that if the count = 0, then the avg = 0.
        
    else:
        avg = 0
        
    return avg

print(doctest.testmod())