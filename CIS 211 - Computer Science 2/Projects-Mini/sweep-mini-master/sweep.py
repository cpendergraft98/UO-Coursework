"""
CIS 211 Mini Project 2- Sweep
AUTHOR: Cole Pendergraft
"""

def all_same(l: list):
    if (len(l) == 0):
        return True
    else:
        count = 0
        for i in range(len(l)):
            search = l[0]
            if search == l[i]:
                count += 1
        return (count == len(l))

def dedup(l: list) -> list:
    new_l = []
    if (len(l) == 0):
        return new_l
    else:
        for i in l:
            if i not in new_l:
                new_l.append(i)
    return new_l

def max_run(l: list) -> int:
    if len(l) == 0:
        return int(0)
    elif len(l) == 1:
        return int(1)
    else:
        count_list = []
        initial = l[0]
        count = 0
        for i in l:
            if i == initial:
                count += 1
                #print(f"The current run for the int {i} is", count) #Used this for debugging
            else:
                count_list.append(count)
                #print(f"The current countlist after the end of the run of this int:", count_list) #Used this for debugging
                initial = i
                #print(f"The new valuue to be searched for is {initial}") #Used this for debugging
                count = 1
        count_list.append(count)
        return max(count_list)

l1 = [1,1,1,1]
l2 = [1,1,1,2]
l3 = []

l4 = [1,1,2,1,1]
l5 = [1,2,3,3,2,1]
l6 = []

l7 = [1,1,2,3,3,3,4,4]
l8 = [3,4,5,5,5]
l9 = [1]

if __name__ == "__main__":
    print(all_same(l1))
    print(all_same(l2))
    print(all_same(l3))
    print(dedup(l4))
    print(dedup(l5))
    print(dedup(l6))
    print(max_run(l7))
    print(max_run(l8))
    print(max_run(l9))