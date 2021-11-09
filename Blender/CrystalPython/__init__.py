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
from ui.meshing_ui import MeshingUI
from ui.particle_system_generate_ui import ParticleSystemGenerateUI
from ui.particle_system_import_ui import ParticleSystemImportUI
from ui.particle_system_export_ui import ParticleSystemExportUI
from ui.fluid_ui import FluidUI
from ui.boundary_ui import BoundaryUI
from ui.solver_ui import SolverUI
from ui.particle_system_animation_ui import ParticleSystemAnimationUI
from ui.particle_system_sequense_import_ui import ParticleSystemSequenceImportUI
from ui.particle_system_sequence_meshing_ui import ParticleSystemSequenceMeshingUI
from ui.triangle_mesh_sequence_import_ui import TriangleMeshSequenceImportUI
from ui.model import Model 
from ui.panel_sample import SampleUI

def register():
  VoxelizerUI.register()
  MeshingUI.register()
#  ParticleSystemGenerateUI.register()
#  ParticleSystemAnimationUI.register()
#  ParticleSystemImportUI.register()
#  ParticleSystemExportUI.register()
  ParticleSystemSequenceImportUI.register()
  ParticleSystemSequenceMeshingUI.register()
  TriangleMeshSequenceImportUI.register()
  FluidUI.register()
  BoundaryUI.register()
  SolverUI.register()
#  SampleUI.register()

  #bpy.types.Scene.tutorial_comment = StringProperty(default = "")

def unregister():
  Model.scene.clear(0)
  Model.scene.clear(1)

  MeshingUI.unregister()
  VoxelizerUI.unregister()
#  ParticleSystemGenerateUI.unregister()
#  ParticleSystemAnimationUI.unregister()
#  ParticleSystemImportUI.unregister()
#  ParticleSystemExportUI.unregister()
  ParticleSystemSequenceImportUI.unregister()
  ParticleSystemSequenceMeshingUI.unregister()
  TriangleMeshSequenceImportUI.unregister()
  FluidUI.unregister()
  BoundaryUI.unregister()
  SolverUI.unregister()
#  SampleUI.unregister()

  #del bpy.types.Scene.tutorial_comment

if __name__ == "__main__":
  register()
