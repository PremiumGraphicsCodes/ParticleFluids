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

class VDB_TOOLS_OT_FilterOperator(bpy.types.Operator) :
  bl_idname = "pg.filteroperator"
  bl_label = "Filter"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      #divide_length = context.scene.smoothing_property.divide_length_prop
      #export_dir_path = bpy.path.abspath(context.scene.smoothing_property.export_directory_prop)

      selected_mesh = self.get_selected_volume(context)
      if selected_mesh == None :
        return {'CANCELLED'}

      vol = selected_mesh.data
      filepath = vol.filepath

      print(filepath)

      j = self.to_json()
      print(json.dumps(j, ensure_ascii=False, indent=2))

      return {'FINISHED'}

  def get_selected_volume(self, context) :
    for o in bpy.data.objects:
      if o.type == 'VOLUME' and o.select_get():
        return o
    return None

  def to_json(self) :
    data = dict()
    data["VDBFileRead"] = [
      {"FilePath": "../VDBDataSet/torus.vdb"},
      {"Radius": 0.5}
    ]
    data["VDBSmoothing"] = [
      {"FilterType": "Median"},
      {"Iteration": 1},
      {"VDBVolumeId": 1},
      {"Width": 1}
    ]
    data["OpenVDBFileWrite"] = [
      {"FilePath": "../VDBDataSet/torus_smooth.vdb"},
      {"ParticleSystemIds": []},
      {"VDBVolumeIds": [1]}
    ]
    return data

class FilterPropertyGroup(bpy.types.PropertyGroup):
  iteration_prop : bpy.props.IntProperty(
    name="iteration",
    description="",
    default=1,
    min = 1
  )
  width_prop : bpy.props.IntProperty(
      name="width",
      description="",
      default=1,
      min=1
  )
  type_prop: bpy.props.EnumProperty(
        name="Type",
        description="",
        default='Median',
        items=[
            ('Median', "Median", ""),
            ('Mean', "Mean", ""),
        ]
    )

class VDB_TOOLS_PT_FilterPanel(bpy.types.Panel) :
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "VDBTools"
  bl_label = "Filter"
  
  def draw(self, context):
    layout = self.layout
    layout.prop(context.scene.filter_property, "iteration_prop", text="Iteration")
    layout.prop(context.scene.filter_property, "width_prop", text="Width")
    layout.prop(context.scene.filter_property, "type_prop", text="Type")
    layout.operator(VDB_TOOLS_OT_FilterOperator.bl_idname, text="Filter")

classes = [
  VDB_TOOLS_OT_FilterOperator,
  VDB_TOOLS_PT_FilterPanel,
  FilterPropertyGroup
]

class VDB_TOOLS_Filter_UI :
  def register():
    for c in classes:
      bpy.utils.register_class(c)
    bpy.types.Scene.filter_property = bpy.props.PointerProperty(type=FilterPropertyGroup)

  def unregister() :
    del bpy.types.Scene.filter_property
    for c in classes:
      bpy.utils.unregister_class(c)
 