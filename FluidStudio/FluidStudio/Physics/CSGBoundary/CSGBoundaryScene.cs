using PG.Core.Math;
using PG.Scene;
using Reactive.Bindings;
using CreateLabels = PG.CSGBoundarySceneCreateLabels;
using UpdateLabels = PG.CSGBoundarySceneUpdateLabels;

namespace FluidStudio.Physics
{
    public class CSGBoundaryScene : IPhysicsScene
    {
        public int Id { get; private set; }

        public string Name { get; private set; }

        public Box3d BoundingBox { get; private set; }

        public IPhysicsScene Parent { get; private set; }

        public CSGBoundaryScene(SolverScene parent, SceneList world, string name, Box3d bb)
        {
            this.Parent = parent;
            Create(world, name, bb);
        }
        
        public void Create(SceneList world, string name, Box3d bb)
        {
            var command = new PG.CLI.PhysicsCommand(CreateLabels.CommandNameLabel);
            command.Execute(world.Adapter);
            this.Id = command.GetResult<int>(CreateLabels.NewIdLabel);
            this.Name = name;
            this.BoundingBox = bb;
            Update(world, name, bb);
        }

        public void Update(SceneList world, string name, Box3d bb)
        {
            this.BoundingBox = bb;
            var command = new PG.CLI.PhysicsCommand(UpdateLabels.CommandNameLabel);
            command.SetArg(UpdateLabels.IdLabel, Id);
            command.SetArg(UpdateLabels.NameLabel, name);
            command.SetArg(UpdateLabels.BoundingBoxLabel, bb);
            command.Execute(world.Adapter);
            this.Name = name;
        }
    }
}
