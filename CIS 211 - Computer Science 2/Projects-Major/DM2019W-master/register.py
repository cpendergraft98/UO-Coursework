"""
A Duck Machine register holds a 32 bit integer. 
The Zero register is special: It always holds 0. 
"""

# Registers are numbered from 0 to 15, and have names
# like r3, r15, etc.  Two special registers have additional
# names:  r0 is called 'zero' because on the DM2020W it always
# holds value 0, and r15 is called 'pc' because it is used to
# hold the program counter.
#

class Register(object):
    """Holds a 32-bit integer"""

    def __init__(self):
        self.value = 0

    def get(self) -> int:
        return self.value

    def put(self, value) -> None:
        self.value = value

class ZeroRegister(Register):
    """A register whose value can never change"""
    
    def put(self, value) -> None:
        pass

    
