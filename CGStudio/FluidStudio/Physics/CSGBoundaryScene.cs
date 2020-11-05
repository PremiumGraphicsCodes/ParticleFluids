using PG.Core.Math;
using PG.Scene;
using Labels = PG.CSGBoundarySceneCreateLabels;

namespace FluidStudio.Physics
{
    public class CSGBoundaryScene
    {
        private int id;

        public CSGBoundaryScene(SceneList world, string name, Box3d box)
        {
            var command = new PG.CLI.PhysicsCommand(Labels.CommandNameLabel);
            command.SetArg(Labels.BoxLabel, box);
            command.Execute(world.Adapter);
            this.id = command.GetResult<int>(Labels.NewIdLabel);
        }
    }
}
