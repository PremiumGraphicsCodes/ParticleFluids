import bpy
import CrystalPLI
import scene

from scene.particle_system_scene import *
from scene import *

class BLParticleSystem :
  def __init__(self, scene):
    self.ps = ParticleSystemScene(scene)

  def convert_to_polygon_mesh(self, ob_name):
      # Create new mesh and a new object
      me = bpy.data.meshes.new(name = ob_name + "Mesh")
      ob = bpy.data.objects.new(ob_name, me)

      positions = self.ps.get_positions()
      coords = []
      for p in positions.values :
        coords.append( (p.x, p.y, p.z))
      # Make a mesh from a list of vertices/edges/faces
      me.from_pydata(coords, [], [])

      # Display name and update the mesh
      ob.show_name = True
      me.update()
      bpy.context.collection.objects.link(ob)
