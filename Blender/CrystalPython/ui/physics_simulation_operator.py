import bpy

from ui.model import Model as model
from physics.solver_scene import SolverScene
from ui.bl_fluid import BLFluid
from CrystalPLI import Vector3dd, Vector3ddVector, Vector3df, Box3dd
from physics.csg_boundary_scene import CSGBoundaryScene

def get_position(box, u, v, w) :
    lx = box.max.x - box.min.x
    ly = box.max.y - box.min.y
    lz = box.max.z - box.min.z
    x = lx * u + box.min.x
    y = ly * v + box.min.y
    z = lz * w + box.min.z
    return Vector3dd(x,y,z)

class BLBoundary :
    def __init__(self, scene) :
        pass

    def build(self) :
        self.boundary = CSGBoundaryScene(model.scene)
        self.boundary.create()
        self.boundary.bounding_box = Box3dd(Vector3dd(0,0,0), Vector3dd(10,10,10))
        self.boundary.send()

    def convert_to_polygon_mesh(self, name) :
        box = self.boundary.bounding_box

        positions = Vector3ddVector()
        positions.add(get_position(box, 0.0, 0.0, 0.0))
        positions.add(get_position(box, 1.0, 0.0, 0.0))
        positions.add(get_position(box, 1.0, 1.0, 0.0))
        positions.add(get_position(box, 0.0, 1.0, 0.0))
        positions.add(get_position(box, 0.0, 0.0, 1.0))
        positions.add(get_position(box, 1.0, 0.0, 1.0))
        positions.add(get_position(box, 1.0, 1.0, 1.0))
        positions.add(get_position(box, 0.0, 1.0, 1.0))

        edges = []
        edges.append((0,1))
        edges.append((1,2))
        edges.append((2,3))
        edges.append((3,0))

        edges.append((4,5))
        edges.append((5,6))
        edges.append((6,7))
        edges.append((7,4))

        edges.append((0,4))
        edges.append((1,5))
        edges.append((2,6))
        edges.append((3,7))
        
        self.me = bpy.data.meshes.new(name = name + "Mesh")
        ob = bpy.data.objects.new(name, self.me)
        
        coords = []
        for p in positions.values :
            coords.append( (p.x, p.y, p.z))
        self.me.from_pydata(coords, edges, [])
        
        ob.show_name = True
        self.me.update()
        bpy.context.collection.objects.link(ob)

class Simulator :
    def __init__(self) :
        self.solver = None
        self.__running = False
        self.fluid = BLFluid(model.scene)
        self.boundary = BLBoundary(model.scene)

    def build(self):
        if self.solver != None :
            return

        self.fluid.build()
        self.fluid.convert_to_polygon_mesh("BLFluid")

        self.boundary.build()
        self.boundary.convert_to_polygon_mesh("BLBoundary")

        self.solver = SolverScene(model.scene)
        self.solver.create()
        
        fluids = []
        fluids.append(self.fluid.fluid)

        boundaries = []
        boundaries.append(self.boundary.boundary)

        self.solver.time_step = 0.03
        self.solver.effect_length = 2.25
        self.solver.send(fluids, boundaries, Vector3df(0.0,0.0,-9.8))
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
                simulator.build()
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
