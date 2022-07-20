"""
CIS 211 Lab 3

AUTHOR: Cole Pendergraft
"""
import math
#from math import pi

class Shape3D:

    def __init__(self):
        raise NotImplementedError("Cannot instantiate object of Shape3D")

    def volume(self) -> float:
        raise NotImplementedError("Not implemented for abstract class")

    def area(self) -> float:
        raise NotImplementedError("Not implemented for abstract class")

    def print_info(self):
        print(f'Area: {self.area()}  |  Volume: {self.volume}')

class Cylinder(Shape3D):

    def __init__(self, radius: float, height: float):
        self.radius = radius
        self.height = height

    def volume(self) -> float:
        return math.pi * self.radius ** 2 * self.height

    def area(self) -> float:
        return 2 * math.pi * self.radius ** 2 \
            * 2 * math.pi * self.radius * self.height

class Cuboid(Shape3D):
    def __init__(self, width: float, length:float, height: float):
        self.width = width
        self.length = length
        self.height = height

    def volume(self) -> float:
        return self.width * self.length * self.height

    def area(self) -> float:
        return 2 * self.width * self.length * 2 \
               * self.width * self.height * 2 \
               * self.length * self.height

class Cube(Cuboid, object):

    def __init__(self, width):
        super().__init__(width, width, width)
        # print (f"width: {self.width}")
        # print(f"length: {self.length}")

    #def volume(self) -> float:
    #    return 1

   # def area(self) -> float:
    #    return super().volume()

if __name__ == '__main__':
    # s= Shape3D()
    # print(s)
    # s.volume()
    c = Cylinder(2,8)
    print(c.volume())
    print(c.area())
    c.print_info()

    d = Cuboid(2, 3, 4)
    print(d.volume())
    print(d.area())
    d.print_info()

    cube = Cube(3)
    print(cube.volume())
    print(cube.area())
    cube.print_info