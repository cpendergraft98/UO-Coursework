'''
CIS Minor Project 4 - Where's Waldo

AUTHOR: Cole Pendergraft

Special Thanks/Credit/Helped By:
Andrew Harper
Thomas Joyce
'''

def all_row_exists_waldo(collection) -> bool:  #Done
    if len(collection) == 0:
        return True
    else:
        for row in collection:
            if "W" not in row:
                return False
        return True

def all_col_exists_waldo(collection) -> bool:  #Done #Tricky
    exists = True
    if len(collection) == 0:
        return True
    for col in range(len(collection[0])):
        value = 0
        for row in range(len(collection)):
            if collection[row][col] == 'W':
                value += 1
        if value >= 1:
            exists = True
        else:
            return False
    return exists

def all_row_all_waldo(collection) -> bool:  #Done
    for row in collection:
        for x in row:
            if x != "W":
                return False
    return True

def all_col_all_waldo(collection) -> bool:  #Done
    for row in collection:
        for x in row:
            if x != "W":
                return False
    return True

def exists_row_exists_waldo(collection) -> bool:  #Done
    for row in collection:
        if "W" in row:
            return True
    return False

def exists_col_exists_waldo(collection) -> bool:  #Done
    for row in collection:
        if "W" in row:
            return True
    return False

def exists_row_all_waldo(collection) -> bool:  #Done
    for row in range(len(collection)):
        if "." not in collection[row]:
            return True
    return False

def exists_col_all_waldo(collection) -> bool: #Done #Tricky
    if len(collection) == 0:
        return False
    for col in range(len(collection[0])):
        value = 0
        for row in range(len(collection)):
            if collection[row][col] == 'W':
                value += 1
        if value == len(collection):
            return True
    return False