﻿using PG.Core.Math;
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

    }
}
