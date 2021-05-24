using FluidStudio.Space;
using FluidStudio.VDB;
using Microsoft.Win32;
using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;
using System.Collections.Generic;

namespace FluidStudio.Tool.Modeling
{
    public class MeshToPSViewModel
    {
        public ReactiveCommand ImportCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand ExportCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<double> DivideLength { get; }
            = new ReactiveProperty<double>(1.0);

        public ReactiveProperty<bool> IsSurfaceOnly { get; }
            = new ReactiveProperty<bool>(false);

        private readonly SpaceModel space;

        private readonly VDBModel vdb;

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        private int pointId;

        public MeshToPSViewModel(MainModel mainModel, SceneList scenes, Canvas3d canvas)
        {
            this.space = mainModel.SpaceModel;
            this.vdb = mainModel.VDBModel;
            this.world = scenes;
            this.canvas = canvas;
            this.ImportCommand.Subscribe(OnImport);
            this.ExportCommand.Subscribe(OnExport);
        }

        private void OnImport()
        {
            var dialog = new OpenFileDialog
            {
                Title = "Import",
                Filter = "OBJFile(*.obj)|*.obj|AllFiles(*.*)|*.*",
            };
            if (dialog.ShowDialog() != true)
            {
                return;
            }

            if (IsSurfaceOnly.Value)
            {
                var meshId = world.ImportOBJ(dialog.FileName);
                var voxelId = space.CreateVoxel("", 1);
                space.PolygonToVoxel(meshId, voxelId, DivideLength.Value);
                canvas.Render();
            }
            else
            {
                var meshId = vdb.ReadOBJ(dialog.FileName);
                canvas.BuildShader(world, meshId);
                canvas.Render();

                var volumeId = MeshToVolume(meshId);
                this.pointId = VolumeToPS(volumeId);
                canvas.Render();
            }
        }

        private int MeshToVolume(int meshId)
        {
            var volumeId = vdb.CreateVDBVolume("VDBVolume", true);
            this.canvas.BuildShader(world, volumeId);

            this.vdb.ConvertMeshToVolume(meshId, volumeId, DivideLength.Value);
            this.canvas.SendShader(world, volumeId);
            return volumeId;
        }

        private int VolumeToPS(int volumeId)
        {
            var psId = vdb.CreateVDBPoints("ConvertedPoints");
            this.canvas.BuildShader(world, psId);

            this.vdb.ConvertVolumeToPS(volumeId, psId);
            this.canvas.SendShader(world, psId);
            return psId;
        }

        private int MeshToVoxel(int meshId)
        {
            var voxelId = space.CreateVoxel("VDBVoxel", 1);
            this.canvas.BuildShader(world, voxelId);

            return voxelId;
        }

        private void OnExport()
        {
            var dialog = new SaveFileDialog
            {
                Title = "Export",
                Filter = "OpenVDBFile(*.vdb)|*.vdb|AllFiles(*.*)|*.*",
            };
            var isOk = dialog.ShowDialog();
            if (isOk == true)
            {
                var pointIds = new List<int>();
                pointIds.Add(this.pointId);
                isOk = vdb.Write(dialog.FileName, pointIds, new List<int>());
                //OnExport(dialog.FileName);
            }
        }
    }
}
