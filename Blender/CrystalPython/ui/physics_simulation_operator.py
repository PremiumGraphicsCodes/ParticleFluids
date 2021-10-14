import bpy
from ui.model import Model as model

from physics.fluid_scene import FluidScene
from physics.solver_scene import SolverScene
from scene.particle_system_scene import ParticleSystemScene
from ui.bl_particle_system import BLParticleSystem
from CrystalPLI import Vector3dd, Vector3ddVector

import bmesh

class BLVolumeBoundary :
    def __init__(self, scene) :
        pass

class BLFluid :
    def __init__(self, scene):
        self.source_ps = None
        self.fluid = None
        self.me = None

    def create(self) :
        self.fluid = FluidScene(model.scene)
        self.source_ps = ParticleSystemScene(model.scene)
        self.source_ps.create_empty("")

        positions = Vector3ddVector()
        for i in range(0,1) :
            for j in range(0,1) :
                for k in range(0,1):
                    positions.add(Vector3dd(i,j,k))

        self.source_ps.set_positions(positions)

        self.fluid.create()
        self.fluid.source_particle_system_id = self.source_ps.id
        self.fluid.send()
        
    def convert_to_polygon_mesh(self, ob_name):
        # Create new mesh and a new object
        self.me = bpy.data.meshes.new(name = ob_name + "Mesh")
        ob = bpy.data.objects.new(ob_name, self.me)
        
        positions = self.fluid.get_positions()
        coords = []
        for p in positions.values :
            coords.append( (p.x, p.y, p.z))
        
        # Make a mesh from a list of vertices/edges/faces
        self.me.from_pydata(coords, [], [])
        
        # Display name and update the mesh
        ob.show_name = True
        self.me.update()
        bpy.context.collection.objects.link(ob)

    def update(self):
        positions = self.fluid.get_positions()
        p = positions.values[0]
        print(p.x)
        print(p.y)
        print(p.z)

        bm = bmesh.new()   # create an empty BMesh
        for p in positions.values:
            bm.verts.new((p.x, p.y, p.z))  # add a new vert
        bm.to_mesh(self.me)
        bm.free()
        self.me.update()

class Simulator :
    def __init__(self) :
        self.solver = None
        self.__running = False
        self.fluid = BLFluid(model.scene)

    def init(self):
        if self.solver != None :
            return

        self.fluid.create()
        self.fluid.convert_to_polygon_mesh("BLFluid")

        self.solver = SolverScene(model.scene)
        self.solver.create()
        
        fluids = []
        fluids.append(self.fluid.fluid)

        self.solver.send(fluids)
        self.solver.simulate()

    def start(self):
        self.__running = True

    def stop(self):
        self.__running = False

    def step(self):
        self.solver.simulate()
        self.fluid.update()

    def is_running(self):
        return self.__running

simulator = Simulator()

class PhysicsSimulationOperator(bpy.types.Operator):
    bl_idname = "pg.physicssimulationoperator"
    bl_label = "PhysicsSimulation"
    bl_description = "Hello"

    def modal(self, context, event):
        active_obj = context.active_object

        if simulator.is_running() :
            simulator.step()

        if context.area:
            context.area.tag_redraw()

        return {'PASS_THROUGH'}

    def invoke(self, context, event):

        if context.area.type == 'VIEW_3D':
            # [開始] ボタンが押された時の処理
            if not simulator.is_running():
                # モーダルモードを開始
                context.window_manager.modal_handler_add(self)
                simulator.init()
                simulator.start()

                print("simulation start")
                return {'RUNNING_MODAL'}
            # [終了] ボタンが押された時の処理
            else:
                simulator.stop()
                print("simulation stop")
                return {'FINISHED'}
        else:
            return {'CANCELLED'}

# UI
class PhysicsSimulationPanel(bpy.types.Panel):
    bl_label = "Start"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "Simulation"
    bl_context = "objectmode"

    def draw(self, context):
        if not simulator.is_running():
            self.layout.operator(PhysicsSimulationOperator.bl_idname,text="Start", icon='PLAY')
        else:
            self.layout.operator(PhysicsSimulationOperator.bl_idname,text="Stop", icon='PAUSE')
