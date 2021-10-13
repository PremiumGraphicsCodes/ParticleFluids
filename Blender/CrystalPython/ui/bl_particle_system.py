import bpy
import bmesh
import CrystalPLI
import scene

from scene.particle_system_scene import *
from scene import *

class BLParticleSystem :
  def __init__(self, scene):
    self.ps = ParticleSystemScene(scene)

  def convert_to_polygon_mesh(self, ob_name):
      # Create new mesh and a new object
      self.me = bpy.data.meshes.new(name = ob_name + "Mesh")
      ob = bpy.data.objects.new(ob_name, self.me)

      positions = self.ps.get_positions()
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
      positions = self.ps.get_positions()
      bm = bmesh.new()   # create an empty BMesh
      for p in positions.values:
        bm.verts.new((p.x, p.y, p.z))  # add a new vert
      bm.to_mesh(self.me)
      bm.free()
      self.me.update()