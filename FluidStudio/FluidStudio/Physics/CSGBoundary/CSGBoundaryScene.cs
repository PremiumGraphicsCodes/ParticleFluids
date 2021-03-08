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

        private readonly SceneList scenes;

        public CSGBoundaryScene(SolverScene parent, SceneList world, string name, Box3d bb)
        {
            this.Parent = parent;
            this.scenes = world;
            Create(name, bb);
        }
        
        public void Create(string name, Box3d bb)
        {
            var command = new PG.CLI.PhysicsCommand(CreateLabels.CommandNameLabel);
            command.Execute(scenes.Adapter);
            this.Id = command.GetResult<int>(CreateLabels.NewIdLabel);
            this.Name = name;
            this.BoundingBox = bb;
            Update(name, bb);
        }

        public void Update(string name, Box3d bb)
        {
            this.BoundingBox = bb;
            var command = new PG.CLI.PhysicsCommand(UpdateLabels.CommandNameLabel);
            command.SetArg(UpdateLabels.IdLabel, Id);
            command.SetArg(UpdateLabels.NameLabel, name);
            command.SetArg(UpdateLabels.BoundingBoxLabel, bb);
            command.Execute(scenes.Adapter);
            this.Name = name;
        }

        public void Delete()
        {
            scenes.Delete(this.Id);
        }
    }
}
