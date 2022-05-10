import bpy

class VDB_TOOLS_OT_CompositeOperator(bpy.types.Operator) :
  bl_idname = "pg.compositeoperator"
  bl_label = "Composite"
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


class CompositePropertyGroup(bpy.types.PropertyGroup):
  type_prop: bpy.props.EnumProperty(
        name="Type",
        description="",
        default='Union',
        items=[
            ('Union', "Union", ""),
            ('Intersection', "Intersection", ""),
            ('Diff', "Diff", "")
        ]
    )

class VDB_TOOLS_PT_Composite_Panel(bpy.types.Panel) :
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "VDBTools"
  bl_label = "Composite"
  
  def draw(self, context):
    layout = self.layout
    layout.prop(context.scene.composite_property, "type_prop", text="Type")
    layout.operator(VDB_TOOLS_OT_CompositeOperator.bl_idname, text="Composite")

classes = [
  VDB_TOOLS_OT_CompositeOperator,
  VDB_TOOLS_PT_Composite_Panel,
  CompositePropertyGroup
]

class VDB_TOOLS_Composite_UI :
  def register():
    for c in classes:
      bpy.utils.register_class(c)
    bpy.types.Scene.composite_property = bpy.props.PointerProperty(type=CompositePropertyGroup)

  def unregister() :
    del bpy.types.Scene.composite_property
    for c in classes:
      bpy.utils.unregister_class(c)
 