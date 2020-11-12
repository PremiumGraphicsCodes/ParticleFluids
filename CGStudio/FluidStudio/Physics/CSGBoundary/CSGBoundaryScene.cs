using PG.Core.Math;
using PG.Scene;
using Reactive.Bindings;
using CreateLabels = PG.CSGBoundarySceneCreateLabels;
using UpdateLabels = PG.CSGBoundarySceneUpdateLabels;

namespace FluidStudio.Physics
{
    public class CSGBoundaryScene : IPhysicsScene
    {
        public int Id { get; }

        public string Name { get; private set; }

        public Box3d Box { get; private set; }

        public CSGBoundaryScene(SceneList world, string name, Box3d box)
        {
            var command = new PG.CLI.PhysicsCommand(CreateLabels.CommandNameLabel);
            command.SetArg(CreateLabels.BoxLabel, box);
            command.Execute(world.Adapter);
            this.Id = command.GetResult<int>(CreateLabels.NewIdLabel);
            this.Name = name;
            this.Box = box;
        }

        public void Update(SceneList world, string name, Box3d box)
        {
            var command = new PG.CLI.PhysicsCommand(UpdateLabels.CommandNameLabel);
            command.SetArg(UpdateLabels.IdLabel, Id);
            command.SetArg(UpdateLabels.NameLabel, name);
            command.SetArg(UpdateLabels.BoxLabel, box);
            this.Name = name;
            this.Box = box;
        }
    }
}
