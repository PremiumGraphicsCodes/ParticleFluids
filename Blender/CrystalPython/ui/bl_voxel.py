import bpy
import CrystalPLI
import scene

from space.voxel_scene import *
from scene import *

class BLVoxel:
  def __init__(self, scene):
    self.voxel = VoxelScene(scene)

  def build(self):
    self.voxel.create_empty_voxel("name")

  def convert_to_polygon_mesh(self, ob_name):
      # Create new mesh and a new object
      me = bpy.data.meshes.new(name = ob_name)
      ob = bpy.data.objects.new(ob_name, me)

      grid = self.voxel.get_values()
      bb = grid.bb

      coords = []
      index = 0
      for x in range(0, grid.res[0]):
        for y in range(0, grid.res[1]):
          for z in range(0, grid.res[2]):
            b = grid.values[index]
            if b :
              coords.append( (x * 0.1, y * 0.1, z * 0.1) )
            index+=1
          
      # Make a mesh from a list of vertices/edges/faces
      me.from_pydata(coords, [], [])

      # Display name and update the mesh
      ob.show_name = True
      me.update()
      bpy.context.collection.objects.link(ob)
