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

        public Box3d Box { get; private set; }

        public CSGBoundaryScene(SceneList world, string name, Box3d box)
        {
            Create(world, name, box);
        }
        
        public void Create(SceneList world, string name, Box3d box)
        {
            var command = new PG.CLI.PhysicsCommand(CreateLabels.CommandNameLabel);
            command.Execute(world.Adapter);
            this.Id = command.GetResult<int>(CreateLabels.NewIdLabel);
            Update(world, name, box);
        }

        public void Update(SceneList world, string name, Box3d box)
        {
            var command = new PG.CLI.PhysicsCommand(UpdateLabels.CommandNameLabel);
            command.SetArg(UpdateLabels.IdLabel, Id);
            command.SetArg(UpdateLabels.NameLabel, name);
            command.SetArg(UpdateLabels.BoxLabel, box);
            command.Execute(world.Adapter);
            this.Name = name;
            this.Box = box;
        }
    }
}
