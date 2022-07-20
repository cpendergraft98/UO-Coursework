"""
Lab 7

AUTHOR: Cole Pendergraft
"""
def multiply(x,y):
    return x * y

func = {"add": lambda x,y: x + y, 'abs': abs}
#print(func['add'](2,3))
#print(func['abs'](-5))

func['multply'] = multiply
#print(func)

func['sub'] = lambda x,y: x-y
#print(func)

l1 = lambda : 5
#print(l1())

l2 = lambda : None
#print(l2())

l3 = lambda x: print(x)
#print(l3(1)) #Prints the value in parentheses, but returns None

for key in func:
    func[key]

def total_sum(list) -> int:
    return sum(list)

def apply(fn: func, list):
    new_list = []
    for i in list:
        new_i = fn(i)
        new_list.append(new_i)
    return new_list

#print(apply(func['abs'], [1, -2, -3]))

func['square'] = lambda x: x**2

def square(list):
    return apply(func['square'], list)

#print(square([1,2,3,4]))

func['sqrt'] = lambda x: x**(1/2)

def magnitude(list):
    new_list = apply(func['square'], list)
    final = sum(new_list)
    return func['sqrt'](final)

#print(magnitude([1,2,3,4,5]))

dispatch_table = {1 : total_sum, 2 : square, 3 : magnitude}

class FunctionDispatcher:
    def __init__(self, dict):
        self.dict = dict

    def process_command(self, key, list):
        return self.dict[key](list)

fd = FunctionDispatcher(dispatch_table)
print(fd.process_command(1, [3,4]))
print(fd.process_command(2, [3,4]))
print(fd.process_command(3, [3,4]))