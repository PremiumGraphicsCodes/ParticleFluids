# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTIBILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

import bpy
import json

import os
import subprocess

class VDB_TOOLS_OT_ResamplingOperator(bpy.types.Operator) :
  bl_idname = "pg.resamplingoperator"
  bl_label = "Resampling"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      export_dir_path = bpy.path.abspath(context.scene.resampling_property.export_directory_prop)

      selected_mesh = self.get_selected_volume(context)
      if selected_mesh == None :
        return {'CANCELLED'}

      vol = selected_mesh.data
      filepath = bpy.path.abspath( vol.filepath )

      print(filepath)

      export_file_path = os.path.join(export_dir_path, os.path.basename(filepath))

      j = self.to_json(filepath, export_file_path, context.scene.resampling_property.type_prop)
      #print(json.dumps(j, ensure_ascii=False, indent=2))

      json_file_path = os.path.join(export_dir_path, "command.json")
      with open(json_file_path, 'w') as f:
        json.dump(j, f, ensure_ascii=False, indent=4)

      addon_dirpath = os.path.dirname(__file__)
      tool_path = os.path.join(addon_dirpath, 'VDBRunner')
      params = []
      params.append(tool_path)
      params.append(json_file_path)        
      
      result = subprocess.run(params, shell=True)
      if result == -1 : 
        return {'CANCELLED'}

      vol = bpy.data.volumes.new(name ="TestVol")
      vol.filepath = export_file_path
      ob = bpy.data.objects.new("TestObj", vol)
      bpy.context.collection.objects.link(ob)

      return {'FINISHED'}

  def get_selected_volume(self, context) :
    for o in bpy.data.objects:
      if o.type == 'VOLUME' and o.select_get():
        return o
    return None

  def to_json(self, input_vdb_file, output_vdb_file, sampling_type) :
    dict1 = dict()
    dict1["FilePath"] =  input_vdb_file
    dict1["Radius"] = 0.5
    data1 = ["VDBFileRead", dict1]

    dict2 = dict()
    dict2["SamplingType"] = sampling_type
    dict2["VolumeId"] = 1
    data2 = ["VDBResampling", dict2]

    dict3 = dict()
    dict3["FilePath"] = output_vdb_file
    dict3["ParticleSystemIds"] = []
    dict3["VDBVolumeIds"] = [1]

    data3 = ["OpenVDBFileWrite", dict3]
    data = dict()
    data = [data1, data2, data3]
    return data

class ResamplingPropertyGroup(bpy.types.PropertyGroup):
  type_prop: bpy.props.EnumProperty(
        name="Type",
        description="",
        default='Box',
        items=[
            ('Point', 'Point', ""),
            ('Box', "Box", ""),
            ('Quadric', "Quadric", ""),
        ]
  )
  export_directory_prop : bpy.props.StringProperty(
    name="export_dir",
    description="Path to Directory",
    default="//",
    maxlen=1024,
    subtype='DIR_PATH',
  )

class VDB_TOOLS_PT_ResamplingPanel(bpy.types.Panel) :
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "VDBTools"
  bl_label = "Resampling"
  
  def draw(self, context):
    layout = self.layout
    layout.prop(context.scene.resampling_property, "type_prop", text="Type")
    layout.prop(context.scene.resampling_property, "export_directory_prop", text="ExportDir")
    layout.operator(VDB_TOOLS_OT_ResamplingOperator.bl_idname, text="Resampling")

classes = [
  VDB_TOOLS_OT_ResamplingOperator,
  VDB_TOOLS_PT_ResamplingPanel,
  ResamplingPropertyGroup
]

class VDB_TOOLS_Resampling_UI :
  def register():
    for c in classes:
      bpy.utils.register_class(c)
    bpy.types.Scene.resampling_property = bpy.props.PointerProperty(type=ResamplingPropertyGroup)

  def unregister() :
    del bpy.types.Scene.resampling_property
    for c in classes:
      bpy.utils.unregister_class(c)
 