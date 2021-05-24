using PG.Core.Math;
using PG.Scene;
using System.Collections.Generic;

namespace FluidStudio.Space
{
    public class SparseVolumeNode
    {
        public int[] Index;
        public float Value;

        public SparseVolumeNode(int[] index, float value)
        {
            this.Index = index;
            this.Value = value;
        }
    }

    public class VoxelNode
    {
        public int[] Index;
        public bool Value;

        public VoxelNode(int[] index, bool value)
        {
            this.Index = index;
            this.Value = value;
        }
    }

    public class SpaceModel
    {
        private readonly SceneList world;

        public SpaceModel(SceneList world)
        {
            this.world = world;
        }

        public int CreateSparseVolume(string name, int[] resolution, Box3d boundingBox, int layer)
        {
            var command = new PG.CLI.SpaceCommand(PG.SparseVolumeSceneCreateLabels.CommandNameLabel);
            command.SetArg(PG.SparseVolumeSceneCreateLabels.ResolutionXLabel, resolution[0]);
            command.SetArg(PG.SparseVolumeSceneCreateLabels.ResolutionYLabel, resolution[1]);
            command.SetArg(PG.SparseVolumeSceneCreateLabels.ResolutionZLabel, resolution[2]);
            command.SetArg(PG.SparseVolumeSceneCreateLabels.BoundingBoxLabel, boundingBox);
            command.SetArg(PG.SparseVolumeSceneCreateLabels.NameLabel, name);
            command.SetArg(PG.SparseVolumeSceneCreateLabels.LayerLabel, layer);
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

        public void SetSparseNodes(int sparseVolumeId, IEnumerable<SparseVolumeNode> nodes)
        {
            var indicesX = new List<int>();
            var indicesY = new List<int>();
            var indicesZ = new List<int>();
            var values = new List<float>();
            foreach(var node in nodes)
            {
                indicesX.Add(node.Index[0]);
                indicesY.Add(node.Index[1]);
                indicesZ.Add(node.Index[2]);
                values.Add(node.Value);
            }

            var command = new PG.CLI.SpaceCommand(PG.SparseVolumeNodeSetLabels.CommandNameLabel);
            command.SetArg(PG.SparseVolumeNodeSetLabels.SparseVolumeIdLabel, sparseVolumeId);
            command.SetArg(PG.SparseVolumeNodeSetLabels.IndicesXLabel, indicesX);
            command.SetArg(PG.SparseVolumeNodeSetLabels.IndicesYLabel, indicesY);
            command.SetArg(PG.SparseVolumeNodeSetLabels.IndicesZLabel, indicesZ);
            command.SetArg(PG.SparseVolumeNodeSetLabels.ValuesLabel, values);
            command.Execute(world.Adapter);
        }

        public int CreateVoxel(string name, int layer)
        {
            var resolution = new int[3];
            resolution[0] = 1;
            resolution[1] = 1;
            resolution[2] = 1;
            var box = new Box3d(new Vector3d(0, 0, 0), new Vector3d(1, 1, 1));
            return CreateVoxel(name, resolution, box, layer);
        }

        public int CreateVoxel(string name, int[] resolution, Box3d boundingBox, int layer)
        {
            var command = new PG.CLI.SpaceCommand(PG.VoxelSceneCreateLabels.CommandNameLabel);
            command.SetArg(PG.VoxelSceneCreateLabels.ResolutionXLabel, resolution[0]);
            command.SetArg(PG.VoxelSceneCreateLabels.ResolutionYLabel, resolution[1]);
            command.SetArg(PG.VoxelSceneCreateLabels.ResolutionZLabel, resolution[2]);
            command.SetArg(PG.VoxelSceneCreateLabels.BoundingBoxLabel, boundingBox);
            command.SetArg(PG.VoxelSceneCreateLabels.NameLabel, name);
            command.SetArg(PG.VoxelSceneCreateLabels.LayerLabel, layer);
            command.Execute(world.Adapter);
            var newId = command.GetResult<int>(PG.VoxelSceneCreateLabels.NewIdLabel);
            var scene = new SceneModel();
            scene.Id.Value = newId;
            scene.Name.Value = name;
            //            scene.SceneType = new PG.Core.SceneType(VDBMeshLabel);
            world.SetName(newId, name);
            world.Add(scene);
            return newId;
        }

        public void SetVoxelNodes(int voxelId, IEnumerable<VoxelNode> nodes)
        {
            var indicesX = new List<int>();
            var indicesY = new List<int>();
            var indicesZ = new List<int>();
            var values = new List<bool>();
            foreach (var node in nodes)
            {
                indicesX.Add(node.Index[0]);
                indicesY.Add(node.Index[1]);
                indicesZ.Add(node.Index[2]);
                values.Add(node.Value);
            }

            var command = new PG.CLI.SpaceCommand(PG.VoxelNodeSetLabels.CommandNameLabel);
            command.SetArg(PG.VoxelNodeSetLabels.VoxelIdLabel, voxelId);
            command.SetArg(PG.VoxelNodeSetLabels.IndicesXLabel, indicesX);
            command.SetArg(PG.VoxelNodeSetLabels.IndicesYLabel, indicesY);
            command.SetArg(PG.VoxelNodeSetLabels.IndicesZLabel, indicesZ);
            command.SetArg(PG.VoxelNodeSetLabels.ValuesLabel, values);
            command.Execute(world.Adapter);
        }

        public void PolygonToVoxel(int polygonId, int voxelId, double divideLength)
        {
            var command = new PG.CLI.SpaceCommand(PG.MeshToVoxelLabels.CommandNameLabel);
            command.SetArg(PG.MeshToVoxelLabels.PolygonMeshIdLabel, polygonId);
            command.SetArg(PG.MeshToVoxelLabels.VoxelIdLabel, voxelId);
            command.SetArg(PG.MeshToVoxelLabels.DivideLengthLabel, divideLength);
            command.Execute(world.Adapter);
        }

        public void VoxelToParticleSystem(int voxelId, int psId)
        {
            var command = new PG.CLI.SpaceCommand(PG.VoxelToPSLabels.CommandNameLabel);
            command.SetArg(PG.VoxelToPSLabels.VoxelIdLabel, voxelId);
            command.SetArg(PG.VoxelToPSLabels.PSIdLabel, psId);
            command.Execute(world.Adapter);
        }

        public void PolygonToParticleSystem(int polygonId, int psId, double divideLength)
        {
            var command = new PG.CLI.SpaceCommand(PG.MeshToPSLabels.CommandNameLabel);
            command.SetArg(PG.MeshToPSLabels.PolygonMeshIdLabel, polygonId);
            command.SetArg(PG.MeshToPSLabels.ParticleSystemIdLabel, psId);
            command.SetArg(PG.MeshToPSLabels.DivideLengthLabel, divideLength);
            command.Execute(world.Adapter);
        }
    }
}
