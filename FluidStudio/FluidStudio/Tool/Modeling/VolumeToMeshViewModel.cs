using FluidStudio.VDB;
using PG.Scene;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.Tool.Modeling
{
    class VolumeToMeshViewModel
    {
        public ReactiveCommand VDBInputDirectorySelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand MeshOutputDirectorySelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<string> VDBInputDirectoryPath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveProperty<string> MeshOutputDirectoryPath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveCommand StartCommand { get; }
            = new ReactiveCommand();

        private SceneList world;

        private VDBModel vdb;

        public VolumeToMeshViewModel(MainModel mainModel)
        {
            this.world = mainModel.Scenes;
            this.vdb = mainModel.VDBModel;
            this.VDBInputDirectorySelectCommand.Subscribe(OnSelectVDBImportDirectory);
            this.MeshOutputDirectorySelectCommand.Subscribe(OnSelectMeshExportDirectory);
            this.StartCommand.Subscribe(OnStart);
        }

        private void OnSelectVDBImportDirectory()
        {
            var dialog = new Microsoft.WindowsAPICodePack.Dialogs.CommonOpenFileDialog();
            dialog.IsFolderPicker = true;
            var result = dialog.ShowDialog();
            if (result == Microsoft.WindowsAPICodePack.Dialogs.CommonFileDialogResult.Ok)
            {
                this.VDBInputDirectoryPath.Value = dialog.FileName;
            }
        }

        private void OnSelectMeshExportDirectory()
        {
            var dialog = new Microsoft.WindowsAPICodePack.Dialogs.CommonOpenFileDialog();
            dialog.IsFolderPicker = true;
            var result = dialog.ShowDialog();
            if (result == Microsoft.WindowsAPICodePack.Dialogs.CommonFileDialogResult.Ok)
            {
                this.MeshOutputDirectoryPath.Value = dialog.FileName;
            }
        }

        private void OnStart()
        {
            var files = System.IO.Directory.GetFiles(this.VDBInputDirectoryPath.Value, "*.vdb");
            foreach (var file in files)
            {
                var vdbIds = vdb.Read(file, 0.5f);
                var meshIds = new List<int>();
                foreach (int id in vdbIds)
                {
                    if (vdb.GetVDBType(id, world) != VDBModel.VDBType.Volume)
                    {
                        continue;
                    }
                    int meshId = vdb.CreateVDBMesh(world, "Mesh");
                    vdb.ConvertVolumeToMesh(id, meshId, world);
                    meshIds.Add(meshId);
                }
                var newName = System.IO.Path.Combine(this.MeshOutputDirectoryPath.Value, "" + System.IO.Path.GetFileNameWithoutExtension(file) + ".obj");
                foreach (var id in meshIds)
                {
                    vdb.WriteOBJ(world, id, newName);
                }
                foreach (int id in vdbIds)
                {
                    world.Delete(id);
                }
                foreach (int id in meshIds)
                {
                    world.Delete(id);
                }
            }
        }
    }
}
