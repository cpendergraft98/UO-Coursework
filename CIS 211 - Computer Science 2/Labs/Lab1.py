'''
CIS 211 Lab 1
Creating a new Fraction class

Cole Pendergraft
'''

def gcd(a, b):
    while a != b:
        if a > b:
            a -= b
        else:
            b -= a
    return a

class Fraction():
    #A class is like a template or a prototype, a box
    #with data and methods (a.k.a. functions)
    
    def simplify(self):
        gcd_ = gcd(self.n, self.d)
        
        self.n = int(self.n / gcd_)
        self.d = int(self.d / gcd_)
    
    def __init__(self, num: int, den: int):
        #Self refers to the object that is being constructed
        assert (num >= 0) and (den > 0), "Denominator cannot be 0, and the Numerator cannot be negative."
        self.n = num
        self.d = den
        self.simplify()
        
    def __str__(self) -> str:
        return f"{self.n}/{self.d}"
    
    def __repr__(self) -> str:
        return f"Fraction({self.n}, {self.d})" 
       
    def __mul__(self, other: "Fraction") -> "Fraction":
        new_n = self.n * other.n
        new_d = self.d * other.d
        return Fraction(new_n, new_d)
    
    def __add__(self, other: "Fraction") -> "Fraction":
        new_d = self.d * other.d
        new_n = (self.n * other.d) + (other.n * self.d)
        return Fraction(new_n, new_d)

    
def main():
    #ClassName (parameters, ...)
    f1 = Fraction(4, 6)
    print(f1)
    f2 = Fraction(15, 20)
    print(f2)
    mul = f1 * f2
    print("Multiplication:", mul)
    add = f1 + f2
    print("Addition:", add)
    
if __name__ == '__main__':
    main()