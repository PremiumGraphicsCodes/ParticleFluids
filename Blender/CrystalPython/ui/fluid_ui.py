import bpy
from CrystalPLI import Vector3dd
from CrystalPLI import Vector3ddVector

from bpy.props import (
    FloatProperty,
)

from physics.fluid_scene import FluidScene
from ui.bl_fluid import BLFluid

from ui.model import Model as model

fluid = BLFluid(model.scene)
particle_radius = 0.2
stiffness = 0.25
viscosity = 10.0

class FluidSourceSelectOperator(bpy.types.Operator) :
  bl_idname = "pg.fluidsourceselectoperator"
  bl_label = "Fluid"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      selected_mesh = self.get_selected_mesh(context)

      global fluid      
      fluid.build()
      fluid.convert_from_polygon_mesh(selected_mesh)
      global particle_radius
      global stiffness
      global viscosity
      fluid.fluid.particle_radius = particle_radius
      fluid.fluid.stiffness = stiffness
      fluid.fluid.viscosity = viscosity
      fluid.fluid.send()
#      self.fluid.fluid.
      return {'FINISHED'}

  def get_selected_mesh(self, context) :
    for o in bpy.data.objects:
      if o.type == 'MESH' and o.select_get():
        return o.to_mesh()
    return None

def set_particle_radius(self, value) :
    global particle_radius
    particle_radius = value
    return None

def get_particle_radius(self):
  global particle_radius
  return particle_radius

def init_props():
    scene = bpy.types.Scene
    scene.particle_radius_prop = FloatProperty(
        name="particle_radius",
        description="ParticleRadius",
        default=0.2,
        min=0.0,
        max=100.0,
        get=get_particle_radius,
        set=set_particle_radius
    )

def clear_props():
    scene = bpy.types.Scene
    del scene.particle_radius_prop

class FluidPanel(bpy.types.Panel) :
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "ParticleFluids"
  bl_label = "Fluid"
  
  def draw(self, context):
    layout = self.layout
    layout.prop(context.scene, "particle_radius_prop", text="ParticleRadius")
    layout.operator(FluidSourceSelectOperator.bl_idname, text="SelectSource")

classes = [
  FluidSourceSelectOperator,
  FluidPanel,
]

class FluidUI :
  def register():
    init_props()
    for c in classes:
      bpy.utils.register_class(c)

  def unregister() :
    clear_props()
    for c in classes:
      bpy.utils.unregister_class(c)
 