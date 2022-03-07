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
import gpu

from physics.fluid_scene import FluidScene
from scene.particle_system_scene import ParticleSystemScene
from CrystalPLI import Vector3dd, Vector3ddVector
from bpy.props import FloatProperty, FloatVectorProperty
from gpu_extras.batch import batch_for_shader

from CrystalPLI import World
from scene.scene import Scene

class BLFluid :
    def __init__(self, scene):
        self.__source_ps = None
        self.__fluid = None
        self.__coords = []
        self.__colors = []

    def get_fluid(self):
        return self.__fluid

    def clear(self) :
        del self.__shader

    def build(self, scene) :
        self.__fluid = FluidScene(scene)
        self.__source_ps = ParticleSystemScene(scene)
        self.__source_ps.create_empty("")

        self.__fluid.create()
        self.__fluid.source_particle_system_id = self.__source_ps.id
        self.__fluid.pressure = 0.25
        self.__fluid.viscosity = 10.0
        self.__fluid.send()

    def convert_from_polygon_mesh(self, obj) :
        mesh = obj.to_mesh()
        matrix_world = obj.matrix_world
        print('---matrix_world---')
        print(matrix_world)

        positions = Vector3ddVector()
        
        print("num of vertices:", len(mesh.vertices))
        for vt in mesh.vertices:
#            print("vertex index:{0:2} co:{1} normal:{2}".format(vt.index, vt.co, vt.normal))
            vvv = matrix_world @ vt.co
            p = Vector3dd(vvv[0], vvv[1], vvv[2])
            positions.add(p)
        self.__source_ps.set_positions(positions)
        self.__fluid.send()
#        self.me = mesh

    def send_shader(self):
        positions = self.__fluid.get_positions()
        self.__coords = []
        self.__colors = []
        for p in positions.values :
            self.__coords.append( (p.x, p.y, p.z))
            self.__colors.append( (1.0, 1.0, 1.0, 1.0))
        
    def render(self, shader):
        if self.__fluid.is_boundary :
            return
        batch = batch_for_shader(shader, 'POINTS', {"pos" : self.__coords, "color" : self.__colors})

        shader.bind()
        matrix = bpy.context.region_data.perspective_matrix
        shader.uniform_float("MVPMatrix", matrix)#        shader.uniform_float("color", color)
        batch.draw(shader)

    def reset(self, prop):
        self.__fluid.particle_radius = prop.particle_radius_prop
        self.__fluid.stiffness = prop.stiffness_prop
        self.__fluid.viscosity = prop.viscosity_prop
        self.__fluid.is_boundary = prop.is_static_prop
        self.__fluid.send()