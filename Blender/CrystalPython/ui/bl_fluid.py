import bpy
import bmesh

from ui.model import Model as model
from physics.fluid_scene import FluidScene
from scene.particle_system_scene import ParticleSystemScene
from CrystalPLI import Vector3dd, Vector3ddVector

class BLFluid :
    def __init__(self, scene):
        self.source_ps = None
        self.fluid = None
        self.me = None

    def build(self) :
        self.fluid = FluidScene(model.scene)
        self.source_ps = ParticleSystemScene(model.scene)
        self.source_ps.create_empty("")

#        positions = Vector3ddVector()
#        for i in range(0,5) :
#            for j in range(0,5) :
#                for k in range(0,5):
#                    positions.add(Vector3dd(i,j,k))#

#        self.source_ps.set_positions(positions)

        self.fluid.create()
        self.fluid.source_particle_system_id = self.source_ps.id
        self.fluid.pressure = 0.25
        self.fluid.viscosity = 10.0
        self.fluid.send()

    def convert_from_polygon_mesh(self, mesh) :
        positions = Vector3ddVector()
        print("num of vertices:", len(mesh.vertices))
        for vt in mesh.vertices:
#            print("vertex index:{0:2} co:{1} normal:{2}".format(vt.index, vt.co, vt.normal))
            p = Vector3dd(vt.co[0], vt.co[1], vt.co[2])
            positions.add(p)
        self.source_ps.set_positions(positions)
        self.fluid.send()
        
    def convert_to_polygon_mesh(self, ob_name):
        # Create new mesh and a new object
        self.me = bpy.data.meshes.new(name = ob_name + "Mesh")
        ob = bpy.data.objects.new(ob_name, self.me)
        
        positions = self.fluid.get_positions()
        coords = []
        for p in positions.values :
            coords.append( (p.x, p.y, p.z))
        
        # Make a mesh from a list of vertices/edges/faces
        self.me.from_pydata(coords, [], [])
        
        # Display name and update the mesh
        ob.show_name = True
        self.me.update()
        bpy.context.collection.objects.link(ob)

    def update(self):
        positions = self.fluid.get_positions()
        p = positions.values[0]
        print(p.x)
        print(p.y)
        print(p.z)

        bm = bmesh.new()   # create an empty BMesh
        for p in positions.values:
            bm.verts.new((p.x, p.y, p.z))  # add a new vert
        bm.to_mesh(self.me)
        bm.free()
        self.me.update()

    def reset(self):
        self.fluid.send()
        self.update()