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

        public string Name { get; set; }

        public Box3d BoundingBox { get; set; }

        public IPhysicsScene Parent { get; private set; }

        private readonly SceneList scenes;

        public CSGBoundaryScene(SolverScene parent, SceneList world)
        {
            this.Parent = parent;
            this.scenes = world;
            var command = new PG.CLI.PhysicsCommand(CreateLabels.CommandNameLabel);
            command.Execute(scenes.Adapter);
            this.Id = command.GetResult<int>(CreateLabels.NewIdLabel);
        }

        public void Send()
        {
            var command = new PG.CLI.PhysicsCommand(UpdateLabels.CommandNameLabel);
            command.SetArg(UpdateLabels.IdLabel, Id);
            command.SetArg(UpdateLabels.NameLabel, Name);
            command.SetArg(UpdateLabels.BoundingBoxLabel, BoundingBox);
            command.Execute(scenes.Adapter);
        }

        public void Delete()
        {
            scenes.Delete(this.Id);
        }
    }
}
