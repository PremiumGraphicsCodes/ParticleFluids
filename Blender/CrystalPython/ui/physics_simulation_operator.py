import bpy
from ui.model import Model as model

from physics.fluid_scene import FluidScene
from physics.solver_scene import SolverScene
from scene.particle_system_scene import ParticleSystemScene
from ui.bl_particle_system import BLParticleSystem
from CrystalPLI import Vector3dd, Vector3ddVector

class Simulator :
    def __init__(self) :
        self.solver = None
        self.ps = None
        self.__running = False
        self.positions = Vector3ddVector()
        self.positions.add(Vector3dd(0,0,0))

    def init(self):
        if self.solver != None :
            return
            
        self.solver = SolverScene(model.scene)
        self.solver.create()

        self.ps = ParticleSystemScene(model.scene)
        self.ps.create_empty("")

        fluids = []
        fluid = FluidScene(model.scene)
        fluid.create()
        fluid.source_particle_system_id = self.ps.id
        fluids.append(fluid)

        self.solver.send(fluids)
        self.solver.simulate()

    def start(self):
        self.__running = True

    def stop(self):
        self.__running = False

    def step(self):
        self.solver.simulate()
        #self.positions = Vector3ddVector()
        #self.positions.add(Vector3dd(10,0,0))
        #self.ps.ps.set_positions(self.positions)
        #self.ps.update()

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
