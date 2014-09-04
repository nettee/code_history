import math
import operator

class Vector:
    """vector in mathematics"""
    def __init__(self, v):
        if (isinstance(v, (list, tuple))):
            self.v = v
            self.length = len(v)
        else:
            raise TypeError("the object for vector must be 'list'")

    def __repr__(self):
        return "Vector({})".format(self.v)
    def __str__(self):
        return str(tuple(self.v))

    def __add__(self, other):
        if self.length == 0:
            raise InvalidOperation("add to Vectors of different length")
        return Vector([a + b for (a, b) in zip(self.v, other.v)])
    def __radd__(self, other):
        return Vector([a + b for (a, b) in zip(other.v, self.v)])
    def __sub__(self, other):
        return Vector([a - b for (a, b) in zip(self.v, other.v)])
    def __rsub__(self, other):
        return Vector([a - b for (a, b) in zip(other.v, self.v)])
    def __rmul__(self, m):
        return Vector([m * a for a in self.v])
    
    @property
    def coordinate(self):
        return tuple(self.v)

class TriVector(Vector):
    """a special vector used for 3-dimension"""
     
    def __repr__(self):
        return "TriVector({})".format(self.v)

    @property
    def x(self):
        return self.v[0]
    @property
    def y(self):
        return self.v[1]
    @property
    def z(self):
        return self.v[2]

class InvalidOperation(Exception):
    pass

def norm(vec):
    return math.sqrt(sum(x * x for x in vec.v))

def dot_product(v1, v2):
    if v1.length != v2.length:
        raise InvalidOperation("two vectors apply dot_product has different length")
    return sum(x * y for (x, y) in zip(v1.v, v2.v))

def cross_product(v1, v2):
    if not isinstance(v1, TriVector) or not isinstance(v2, TriVector):
        raise InvalidOperation("cross_product must use TriVector")
    x = v1.y * v2.z - v1.z * v2.y
    y = v1.z * v2.x - v1.x * v2.z
    z = v1.x * v2.y - v1.y * v2.x
    return TriVector([x, y, z])

if __name__ == '__main__':
    v = Vector((1,2,3,4))
    r = TriVector([11,9,2])
    t = TriVector([4,5,6])
    print("v = {}".format(v))
    print("t = {}".format(t))
    print(v + t)
    print(v - t)
    print(dot_product(r, t))
    print(cross_product(r,t))
    print(norm(Vector([1,2,2])))
