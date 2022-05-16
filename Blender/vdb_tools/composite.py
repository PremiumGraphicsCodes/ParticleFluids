import bpy
import os
import json
import subprocess

class VDB_TOOLS_OT_CompositeOperator(bpy.types.Operator) :
  bl_idname = "pg.compositeoperator"
  bl_label = "Composite"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      #divide_length = context.scene.smoothing_property.divide_length_prop
      export_dir_path = bpy.path.abspath(context.scene.composite_property.export_directory_prop)

      selected_volumes = self.get_selected_volumes(context)
      if len(selected_volumes) != 2 :
        self.report({'INFO'}, "Please select two volumes")
        return {'CANCELLED'}

      filepath = bpy.path.abspath( selected_volumes[0].filepath )

      export_file_path = os.path.join(export_dir_path, os.path.basename(filepath))

      j = self.to_json(filepath, export_file_path)
      print(json.dumps(j, ensure_ascii=False, indent=2))

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

  def get_selected_volumes(self, context) :
    volumes = []
    for o in bpy.data.objects:
      if o.type == 'VOLUME' and o.select_get():
        volumes.append(o.data)
    return volumes

  def to_json(self, input_vdb_file1, input_vdb_file2, output_vdb_file) :
    dict1 = dict()
    dict1["FilePath"] =  input_vdb_file1
    dict1["Radius"] = 0.5
    data1 = ["VDBFileRead", dict1]

    dict2 = dict()
    dict2["FilePath"] =  input_vdb_file2
    dict2["Radius"] = 0.5
    data2 = ["VDBFileRead", dict2]

    dict3 = dict()
    data3 = []

    dict4 = dict()
    dict4["FilePath"] = output_vdb_file
    dict4["ParticleSystemIds"] = []
    dict4["VDBVolumeIds"] = [1]

    data4 = ["OpenVDBFileWrite", dict4]
    data = dict()
    data = [data1, data2, data3, data4]
    return data

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
 