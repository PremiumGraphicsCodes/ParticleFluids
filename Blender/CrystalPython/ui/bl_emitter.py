import bpy
import gpu

from physics.emitter_scene import EmitterScene
from scene.particle_system_scene import ParticleSystemScene
from CrystalPLI import Vector3dd, Vector3ddVector
from bpy.props import FloatProperty, FloatVectorProperty
from gpu_extras.batch import batch_for_shader

from CrystalPLI import World
from scene.scene import Scene

class BLEmitter :
    def __init__(self, scene):
        self.__source_ps = None
        self.__emitter = None
        self.__shader = None
        self.__coords = []
        self.__colors = []

    def get_emitter(self):
        return self.__emitter

    def clear(self) :
        del self.__shader

    def build(self, scene) :
        self.__emitter = EmitterScene(scene)
        self.__source_ps = ParticleSystemScene(scene)
        self.__source_ps.create_empty("")

        self.__emitter.create()
        self.__emitter.set_source_ps_id( self.__source_ps.id )
        self.__emitter.send()

        vertex_shader = """
                    uniform mat4 MVPMatrix;
                    in vec3 pos;
                    in vec4 color;

                    out vec4 vColor;

                    void main()
                    {
                        gl_Position = MVPMatrix * vec4(pos, 1.0);
                        vColor = color;
                    }
        """

        fragment_shader = """
                    in vec4 vColor;

                    void main()
                    {
                        gl_FragColor = vColor;
                    }
        """
        self.__shader = gpu.types.GPUShader(vertex_shader, fragment_shader)

    def convert_from_polygon_mesh(self, mesh) :
        positions = Vector3ddVector()
        print("num of vertices:", len(mesh.vertices))
        for vt in mesh.vertices:
#            print("vertex index:{0:2} co:{1} normal:{2}".format(vt.index, vt.co, vt.normal))
            p = Vector3dd(vt.co[0], vt.co[1], vt.co[2])
            positions.add(p)
        self.__source_ps.set_positions(positions)
        self.__emitter.send()
#        self.me = mesh

    def send_shader(self):
        positions = self.__emitter.get_positions()
        self.__coords = []
        self.__colors = []
        for p in positions.values :
            self.__coords.append( (p.x, p.y, p.z))
            self.__colors.append( (1.0, 1.0, 1.0, 1.0))
        
    def render(self):
        batch = batch_for_shader(self.__shader, 'POINTS', {"pos" : self.__coords, "color" : self.__colors})

        self.__shader.bind()
        matrix = bpy.context.region_data.perspective_matrix
        self.__shader.uniform_float("MVPMatrix", matrix)#        shader.uniform_float("color", color)
        batch.draw(self.__shader)

    def reset(self, prop):
        self.__emitter.set_particle_radius( prop.particle_radius_prop )
        self.__emitter.set_stiffness( prop.stiffness_prop )
        self.__emitter.set_viscosity( prop.viscosity_prop )
        self.__emitter.set_start_step( prop.start_step_prop )
        self.__emitter.set_end_step( prop.end_step_prop )
        self.__emitter.set_interval( prop.interval_prop )
        self.__emitter.set_initial_velocity( prop.initial_velocity_prop )
        self.__emitter.send()