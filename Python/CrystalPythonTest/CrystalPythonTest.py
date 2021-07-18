
import CrystalPython
import unittest

from CrystalPython import add, POINT, Vector3dd


print('doc=', CrystalPython.__doc__)
#x1, y1 = 1, 2
#print("add({},{})=".format(x1, y1), CrystalPython.add(x1, y1))

#x2, y2 = 3, 4

#p = POINT(x1, y1)
#q = POINT([x2, y2])

#print('p=', p)
#print('q=', q)
#print('p+q=', p+q)
#print('p.x,p.y=', p.x, p.y)

class TestVector3dd(unittest.TestCase):
    def test(self):
        v = Vector3dd(1.0,2.0,3.0)
        self.assertEqual(1.0, v.x)
        self.assertEqual(2.0, v.y)
        self.assertEqual(3.0, v.z)

if __name__ == '__main__':
    unittest.main()

#print(vector3dd.x)
#print(vector3dd.y)
#print(vector3dd.z)
#CrystalPython.call("PhysicsSolverCreateCommand");