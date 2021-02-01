using FluidStudio.VDB;
using Microsoft.Win32;
using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.Tool.Modeling
{
    public class MeshToPSViewModel
    {
        public ReactiveCommand ImportCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand ExportCommand { get; }
            = new ReactiveCommand();

        private readonly VDBModel vdb;

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        private int pointId;

        public MeshToPSViewModel(MainModel mainModel, SceneList scenes, Canvas3d canvas)
        {
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
            if (dialog.ShowDialog() == true)
            {
                var meshId = vdb.ReadOBJ(world, dialog.FileName);
                canvas.BuildShader(world, meshId);
                canvas.Render();
                var volumeId = MeshToVolume(meshId);
                this.pointId = VolumeToPS(volumeId);
//                canvas.Renderer.Update(mainMo)
                canvas.Render();
            }
        }

        private int MeshToVolume(int meshId)
        {
            var volumeId = vdb.CreateVDBVolume(world, "VDBVolume", true);
            this.canvas.BuildShader(world, volumeId);

            this.vdb.ConvertMeshToVolume(meshId, volumeId, world);
            this.canvas.SendShader(world, volumeId);
            return volumeId;
        }

        private int VolumeToPS(int volumeId)
        {
            var psId = vdb.CreateVDBPoints(world, "ConvertedPoints");
            this.canvas.BuildShader(world, psId);

            this.vdb.ConvertVolumeToPS(volumeId, psId, world);
            this.canvas.SendShader(world, psId);
            return psId;
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
                isOk = vdb.Write(dialog.FileName, world, pointIds, new List<int>());
                //OnExport(dialog.FileName);
            }
        }
    }
}
