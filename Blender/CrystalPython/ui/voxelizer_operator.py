import bpy

from bpy.props import (
    FloatProperty,
)

from ui.bl_particle_system import BLParticleSystem
from ui.bl_triangle_mesh import BLTriangleMesh
from space.voxel_scene import Voxelizer
from scene.file_io import FileIO

import os
import subprocess

from CrystalPLI import World
from scene.scene import Scene

world = World()
scene = Scene(world)

class VoxelizerOperator(bpy.types.Operator) :
  bl_idname = "pg.voxelizeroperator"
  bl_label = "MeshToPS"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      global scene
      divide_length = context.scene.voxelizer_property.divide_length

      selected_mesh = self.get_selected_mesh(context)
      if selected_mesh == None :
        return
      mesh = BLTriangleMesh(scene)

      mesh_file_path = "tmp_fs_mesh.stl"
      ps_file_path = "tmp_fs_ps.stl"

      mesh.convert_from_polygon_mesh(selected_mesh)
      mesh.mesh.export_stl(mesh_file_path)

      addon_dirpath = os.path.dirname(__file__)
      tool_path = os.path.join(addon_dirpath, '../vdb/MeshToPSTool')
      params = []
      params.append(tool_path)
      params.append("-i")
      params.append(mesh_file_path)
      params.append("-o")
      params.append(ps_file_path)
      params.append("-l")
      params.append(str(divide_length))          
      
      result = subprocess.run(params, shell=True)
      if result != -1 :
        ps = BLParticleSystem(scene)
        ps.ps.create_empty("")
        ps.convert_to_polygon_mesh("")               

        FileIO.import_pcd(scene, ps.ps.id, ps_file_path)
        ps.update()

      return {'FINISHED'}

  def get_selected_mesh(self, context) :
    for o in bpy.data.objects:
      if o.type == 'MESH' and o.select_get():
        return o
        #return o.to_mesh()
    return None

class VoxelizerPropertyGroup(bpy.types.PropertyGroup):
  divide_length : bpy.props.FloatProperty(
    name="divide_length",
    description="",
    default=1.0,
    min = 0.0
  )

class PARTICLE_FLUIDS_Voxelizer_PT_Panel(bpy.types.Panel) :
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "VDBTools"
  bl_label = "Voxelize"
  
  def draw(self, context):
    layout = self.layout
    layout.prop(context.scene.voxelizer_property, "divide_length", text="DivideLength")
    layout.operator(VoxelizerOperator.bl_idname, text="Voxelize")

classes = [
  VoxelizerOperator,
  PARTICLE_FLUIDS_Voxelizer_PT_Panel,
  VoxelizerPropertyGroup
]

class VoxelizerUI :
  def register():
    for c in classes:
      bpy.utils.register_class(c)
    bpy.types.Scene.voxelizer_property = bpy.props.PointerProperty(type=VoxelizerPropertyGroup)

  def unregister() :
    del bpy.types.Scene.voxelizer_property
    for c in classes:
      bpy.utils.unregister_class(c)
 