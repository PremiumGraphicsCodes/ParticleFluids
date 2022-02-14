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
    "name" : "FastFluids",
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

from ui.vdb.voxelizer_operator import VoxelizerUI
from ui.fluid_ui import FluidUI
from ui.solver_ui import SolverUI
from ui.vdb.ps_to_volume_ui import PARTICLE_FLUIDS_PSToVolumeUI
#from ui.sandbox.particle_system_sequense_import_ui import ParticleSystemSequenceImportUI
#from ui.sandbox.triangle_mesh_sequence_import_ui import TriangleMeshSequenceImportUI
#from ui.thread_sample import ThreadSampleUI

def register():
  VoxelizerUI.register()
  PARTICLE_FLUIDS_PSToVolumeUI.register()
  FluidUI.register()
  SolverUI.register()
#  ParticleSystemSequenceImportUI.register()
#  TriangleMeshSequenceImportUI.register()
#  ThreadSampleUI.register()

def unregister():
  VoxelizerUI.unregister()
  PARTICLE_FLUIDS_PSToVolumeUI.unregister()
  FluidUI.unregister()
  SolverUI.unregister()
#  ThreadSampleUI.unregister()
#  ParticleSystemSequenceImportUI.unregister()
#  TriangleMeshSequenceImportUI.unregister()


if __name__ == "__main__":
  register()
