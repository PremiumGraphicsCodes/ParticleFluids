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

bl_info = {
    "name" : "TestVSCode",
    "author" : "PremiumGraphics",
    "description" : "",
    "blender" : (2, 80, 0),
    "version" : (0, 0, 1),
    "location" : "",
    "warning" : "",
    "category" : "Generic"
}

import os
import sys

addon_dirpath = os.path.dirname(__file__)
sys.path += [addon_dirpath]

import bpy

from ui.voxelizer_operator import VoxelizerUI
from ui.ps_to_mesh_operator import PSToMeshOperator
from ui.particle_system_generate_operator import ParticleSystemGenerateOperator
from ui.particle_system_import_operator import ParticleSystemImportOperator
from ui.particle_system_export_operator import ParticleSystemExportOperator
from ui.physics_simulation_operator import PhysicsSimulationUI
from ui.particle_system_animation_operator import ParticleSystemAnimationUI
from ui.particle_system_sequense_import_operator import ParticleSystemSequenceImportUI
from ui.model import Model 
from ui.panel_sample import SampleUI

class ParticleFluidsPanel(bpy.types.Panel):
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "ParticleFluids"
  bl_label = "PanelTitle"

  def draw(self, context):
    layout = self.layout
#    layout.operator(VoxelizerOperator.bl_idname, text="Voxelizer")
    layout.operator(PSToMeshOperator.bl_idname, text="PSToMesh")
    layout.operator(ParticleSystemGenerateOperator.bl_idname, text="PSGenerator")
    layout.operator(ParticleSystemImportOperator.bl_idname, text="PSImport")
    layout.operator(ParticleSystemExportOperator.bl_idname, text="PSExport")

classes = [
  ParticleFluidsPanel,
  PSToMeshOperator,
  ParticleSystemImportOperator,
  ParticleSystemExportOperator,
  ParticleSystemGenerateOperator,
]

def register():
  for c in classes:
    bpy.utils.register_class(c)
  VoxelizerUI.register()
  ParticleSystemAnimationUI.register()
  ParticleSystemSequenceImportUI.register()
  PhysicsSimulationUI.register()
  SampleUI.register()

  #bpy.types.Scene.tutorial_comment = StringProperty(default = "")

def unregister():
  Model.scene.clear(0)
  Model.scene.clear(1)
  for c in classes:
    bpy.utils.unregister_class(c)
  VoxelizerUI.unregister()
  ParticleSystemAnimationUI.unregister()
  ParticleSystemSequenceImportUI.unregister()
  PhysicsSimulationUI.unregister()
  SampleUI.unregister()

  #del bpy.types.Scene.tutorial_comment

if __name__ == "__main__":
  register()
