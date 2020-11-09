using PG.Core.Math;
using PG.Scene;
using Reactive.Bindings;
using Labels = PG.CSGBoundarySceneCreateLabels;

namespace FluidStudio.Physics
{
    public class CSGBoundaryScene
    {
        private int id;

        public int Id { get { return id; } }

        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>();

        public CSGBoundaryScene(SceneList world, string name, Box3d box)
        {
            var command = new PG.CLI.PhysicsCommand(Labels.CommandNameLabel);
            command.SetArg(Labels.BoxLabel, box);
            command.Execute(world.Adapter);
            this.id = command.GetResult<int>(Labels.NewIdLabel);
            this.Name.Value = name;
        }
    }
}
