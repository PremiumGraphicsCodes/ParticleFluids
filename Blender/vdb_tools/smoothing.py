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

import os
import subprocess

class VDB_TOOLS_OT_SmoothingOperator(bpy.types.Operator) :
  bl_idname = "pg.smoothingoperator"
  bl_label = "Smoothing"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      #divide_length = context.scene.smoothing_property.divide_length_prop
      #export_dir_path = bpy.path.abspath(context.scene.smoothing_property.export_directory_prop)

      selected_mesh = self.get_selected_volume(context)
      if selected_mesh == None :
        return {'CANCELLED'}
      return {'FINISHED'}

  def get_selected_volume(self, context) :
    for o in bpy.data.objects:
      if o.type == 'VOLUME' and o.select_get():
        return o
    return None

class SmoothingPropertyGroup(bpy.types.PropertyGroup):
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

class VDB_TOOLS_PT_Smoothing_Panel(bpy.types.Panel) :
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "VDBTools"
  bl_label = "Smoothing"
  
  def draw(self, context):
    layout = self.layout
    layout.prop(context.scene.smoothing_property, "iteration_prop", text="Iteration")
    layout.prop(context.scene.smoothing_property, "width_prop", text="Width")
    layout.prop(context.scene.smoothing_property, "type_prop", text="Type")
    layout.operator(VDB_TOOLS_OT_SmoothingOperator.bl_idname, text="Smoothing")

classes = [
  VDB_TOOLS_OT_SmoothingOperator,
  VDB_TOOLS_PT_Smoothing_Panel,
  SmoothingPropertyGroup
]

class VDB_TOOLS_Smoothing_UI :
  def register():
    for c in classes:
      bpy.utils.register_class(c)
    bpy.types.Scene.smoothing_property = bpy.props.PointerProperty(type=SmoothingPropertyGroup)

  def unregister() :
    del bpy.types.Scene.smoothing_property
    for c in classes:
      bpy.utils.unregister_class(c)
 