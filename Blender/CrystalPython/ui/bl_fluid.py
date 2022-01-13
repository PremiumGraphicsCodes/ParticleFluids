import bpy
import bmesh
import gpu

from ui.model import Model as model
from physics.fluid_scene import FluidScene
from scene.particle_system_scene import ParticleSystemScene
from CrystalPLI import Vector3dd, Vector3ddVector
from bpy.props import FloatProperty, FloatVectorProperty
from gpu_extras.batch import batch_for_shader


class BLFluid :
    def __init__(self, scene):
        self.source_ps = None
        self.fluid = None
        self.shader = None

    def build(self) :
        self.fluid = FluidScene(model.scene)
        self.source_ps = ParticleSystemScene(model.scene)
        self.source_ps.create_empty("")

        self.fluid.create()
        self.fluid.source_particle_system_id = self.source_ps.id
        self.fluid.pressure = 0.25
        self.fluid.viscosity = 10.0
        self.fluid.vorticity = 0.05
        self.fluid.send()

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
        # ビルトインのシェーダを取得
        self.shader = gpu.types.GPUShader(vertex_shader, fragment_shader)


    def convert_from_polygon_mesh(self, mesh) :
        positions = Vector3ddVector()
        print("num of vertices:", len(mesh.vertices))
        for vt in mesh.vertices:
#            print("vertex index:{0:2} co:{1} normal:{2}".format(vt.index, vt.co, vt.normal))
            p = Vector3dd(vt.co[0], vt.co[1], vt.co[2])
            positions.add(p)
        self.source_ps.set_positions(positions)
        self.fluid.send()
#        self.me = mesh
        
    def render(self):
        positions = self.fluid.get_positions()
        coords = []
        colors = []
        for p in positions.values :
            coords.append( (p.x, p.y, p.z))
            colors.append( (1.0, 1.0, 1.0, 1.0))

        # バッチを作成
        batch = batch_for_shader(self.shader, 'POINTS', {"pos" : coords, "color" : colors})

        # シェーダのパラメータ設定
#        color = [0.5, 1.0, 1.0, 1.0]
        self.shader.bind()
        matrix = bpy.context.region_data.perspective_matrix
        self.shader.uniform_float("MVPMatrix", matrix)#        shader.uniform_float("color", color)

        # 描画
        batch.draw(self.shader)

    def reset(self, prop):
        self.fluid.particle_radius = prop.particle_radius_prop
        self.fluid.stiffness = prop.stiffness_prop
        self.fluid.viscosity = prop.viscosity_prop
        self.fluid.vorticity = prop.vorticity_prop
        self.fluid.is_boundary = prop.is_static_prop
        self.fluid.send()