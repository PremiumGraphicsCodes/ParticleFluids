import physics_labels
from scene import Scene
from CrystalPLI import *

class SolverScene :
    def __init__(self, scene) :
        self.scene = scene

    def create(self) :
        create_physics_command(physics_labels.PhysicsSolverCreateLabels.CommandNameLabel)
        isOk = execute_command(self.scene.world)
        #self.assertTrue(isOk)
        newId = get_result_int(physics_labels.PhysicsSolverCreateLabels.NewIdLabel)
        return newId

class FluidScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = 0
        self.source_particle_system_id = 0
        self.particle_radius = 1.0
        self.density = 1.0
        self.stiffness = 1.0
        self.viscosity = 1.0
        self.is_boundary = False;
        self.name = ""

    def create(self) :
        create_physics_command(physics_labels.FluidSceneCreateLabels.CommandNameLabel)
        execute_command(self.scene.world)
        self.id = get_result_int(physics_labels.FluidSceneCreateLabels.NewIdLabel)

    def send(self) :
        create_physics_command(physics_labels.FluidSceneUpdateLabels.CommandNameLabel)
        set_arg_int(physics_labels.FluidSceneUpdateLabels.IdLabel, self.id)
        set_arg_int(physics_labels.FluidSceneUpdateLabels.ParticleSystemIdLabel, self.source_particle_system_id)
        set_arg_float(physics_labels.FluidSceneUpdateLabels.ParticleRadiusLabel, self.particle_radius)
        set_arg_float(physics_labels.FluidSceneUpdateLabels.DensityLabel, self.density)
        set_arg_float(physics_labels.FluidSceneUpdateLabels.StiffnessLabel, self.stiffness)
        set_arg_float(physics_labels.FluidSceneUpdateLabels.ViscosityLabel, self.viscosity)
        set_arg_bool(physics_labels.FluidSceneUpdateLabels.IsBoundary, self.is_boundary)
        set_arg_string(physics_labels.FluidSceneUpdateLabels.NameLabel, self.name)
        is_ok = execute_command(self.scene.world)
        return is_ok

class CSGBoundaryScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = 0
        self.name = ""
        self.bounding_box = Box3dd()

    def create(self) :
        create_physics_command(physics_labels.CSGBoundarySceneCreateLabels.CommandNameLabel)
        execute_command(self.scene.world)
        self.id = get_result_int(physics_labels.FluidSceneCreateLabels.NewIdLabel)

    def send(self) :
        create_physics_command(physics_labels.CSGBoundarySceneUpdateLabels.CommandNameLabel)
        set_arg_int(physics_labels.CSGBoundarySceneUpdateLabels.IdLabel, self.id)
        set_arg_string(physics_labels.CSGBoundarySceneUpdateLabels.NameLabel, self.name)
        set_arg_box3dd(physics_labels.CSGBoundarySceneUpdateLabels.BoundingBoxLabel, self.bounding_box)
        is_ok = execute_command(self.scene.world)
        return is_ok
    
    def delete(self) :
        self.scene.delete(self.id, False)