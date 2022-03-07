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
from bpy.props import IntProperty, FloatProperty, FloatVectorProperty, BoolProperty

class PARTICLE_FLUID_EmitterProperty(bpy.types.PropertyGroup) :
  is_active_prop : BoolProperty(
    name="is_active",
    description="Active",
    default = False,
  )
  stiffness_prop : bpy.props.FloatProperty(
    name="stiffness",
    description="Stiffness",
    default=100.0,
    min = 0.0,
  )
  particle_radius_prop : FloatProperty(
    name="particle_radius",
    description="ParticleRadius",
    default=1.0,
    min=0.0,
  )
  viscosity_prop : FloatProperty(
    name="viscosity",
    description="Viscosity",
    default = 10.0,
    min = 0.0,
  )
  start_step_prop : IntProperty(
    name="start_step",
    description="StartStep",
    default=1,
    min=0
  )
  end_step_prop : IntProperty(
    name="end_step",
    description="EndStep",
    default=100,
    min=0
  )
  interval_prop : IntProperty(
    name="interval",
    description="Interval",
    default=5,
    min=1
  )
  initial_velocity_prop : FloatVectorProperty(
    name="initial_velocity",
    description="InitialVelocity",
    default=(0.0, 0.0, 0.0)
    )

