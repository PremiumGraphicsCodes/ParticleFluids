from CrystalPLI import World
from scene.scene import Scene
from physics.solver_scene import SolverScene

class Model :
  world = World()
  scene = Scene(world)
  solver = SolverScene(scene)