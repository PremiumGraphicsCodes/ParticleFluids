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

        public int SolidId { get; private set; }

        public CSGBoundaryScene(SceneList world, string name, int solidId)
        {
            Create(world, name, solidId);
        }
        
        public void Create(SceneList world, string name, int solidId)
        {
            var command = new PG.CLI.PhysicsCommand(CreateLabels.CommandNameLabel);
            command.Execute(world.Adapter);
            this.Id = command.GetResult<int>(CreateLabels.NewIdLabel);
            this.Name = name;
            this.SolidId = solidId;
            Update(world, name, solidId);
        }

        public void Update(SceneList world, string name, int solidId)
        {
            var command = new PG.CLI.PhysicsCommand(UpdateLabels.CommandNameLabel);
            command.SetArg(UpdateLabels.IdLabel, Id);
            command.SetArg(UpdateLabels.NameLabel, name);
            command.SetArg(UpdateLabels.SolidIdLabel, solidId);
            command.Execute(world.Adapter);
            this.Name = name;
        }
    }
}
