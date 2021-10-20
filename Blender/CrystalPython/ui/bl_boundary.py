import bpy
from CrystalPLI import Vector3dd, Vector3ddVector, Box3dd
from physics.csg_boundary_scene import CSGBoundaryScene
from ui.model import Model as model

def get_position(box, u, v, w) :
    lx = box.max.x - box.min.x
    ly = box.max.y - box.min.y
    lz = box.max.z - box.min.z
    x = lx * u + box.min.x
    y = ly * v + box.min.y
    z = lz * w + box.min.z
    return Vector3dd(x,y,z)

class BLBoundary :
    def __init__(self, scene) :
        pass

    def build(self) :
        self.boundary = CSGBoundaryScene(model.scene)
        self.boundary.create()
        self.boundary.bounding_box = Box3dd(Vector3dd(0,0,0), Vector3dd(10,10,10))
        self.boundary.send()

    def convert_to_polygon_mesh(self, name) :
        box = self.boundary.bounding_box

        positions = Vector3ddVector()
        positions.add(get_position(box, 0.0, 0.0, 0.0))
        positions.add(get_position(box, 1.0, 0.0, 0.0))
        positions.add(get_position(box, 1.0, 1.0, 0.0))
        positions.add(get_position(box, 0.0, 1.0, 0.0))
        positions.add(get_position(box, 0.0, 0.0, 1.0))
        positions.add(get_position(box, 1.0, 0.0, 1.0))
        positions.add(get_position(box, 1.0, 1.0, 1.0))
        positions.add(get_position(box, 0.0, 1.0, 1.0))

        edges = []
        edges.append((0,1))
        edges.append((1,2))
        edges.append((2,3))
        edges.append((3,0))

        edges.append((4,5))
        edges.append((5,6))
        edges.append((6,7))
        edges.append((7,4))

        edges.append((0,4))
        edges.append((1,5))
        edges.append((2,6))
        edges.append((3,7))
        
        self.me = bpy.data.meshes.new(name = name + "Mesh")
        ob = bpy.data.objects.new(name, self.me)
        
        coords = []
        for p in positions.values :
            coords.append( (p.x, p.y, p.z))
        self.me.from_pydata(coords, edges, [])
        
        ob.show_name = True
        self.me.update()
        bpy.context.collection.objects.link(ob)
