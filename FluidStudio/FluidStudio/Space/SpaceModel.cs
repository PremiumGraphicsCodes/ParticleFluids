using PG.Core.Math;
using PG.Scene;

namespace FluidStudio.Space
{
    public class SpaceModel
    {
        private readonly SceneList world;

        public SpaceModel(SceneList world)
        {
            this.world = world;
        }

        public int CreateSparseVolume(string name, int[] resolution, Box3d boundingBox)
        {
            var command = new PG.CLI.SpaceCommand(PG.SparseVolumeSceneCreateLabels.CommandNameLabel);
            command.SetArg(PG.SparseVolumeSceneCreateLabels.ResolutionLabel, resolution);
            command.SetArg(PG.SparseVolumeSceneCreateLabels.BoundingBoxLabel, boundingBox);
            command.Execute(world.Adapter);
            var newId = command.GetResult<int>(PG.VDBSceneCreateLabels.NewIdLabel);
            var scene = new SceneModel();
            scene.Id.Value = newId;
            scene.Name.Value = name;
//            scene.SceneType = new PG.Core.SceneType(VDBMeshLabel);
            world.SetName(newId, name);
            world.Add(scene);
            return newId;
        }

    }
}
