using FluidStudio.VDB;
using PG.Scene;
using Reactive.Bindings;
using System.Collections.Generic;
using System.Linq;

namespace FluidStudio.Tool.Modeling
{
    public class PSToVolumeViewModel
    {
        public ReactiveCommand VDBInputDirectorySelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand VDBOutputDirectorySelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<string> VDBInputDirectoryPath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveProperty<string> VDBOutputDirectoryPath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveProperty<float> Threshold { get; }
            = new ReactiveProperty<float>(2.0f);

        public ReactiveCommand StartCommand { get; }
            = new ReactiveCommand();

        private SceneList world;

        private VDBModel vdb;

        public PSToVolumeViewModel(MainModel mainModel)
        {
            this.world = mainModel.Scenes;
            this.vdb = mainModel.VDBModel;
            this.VDBInputDirectorySelectCommand.Subscribe(OnSelectVDBImportDirectory);
            this.VDBOutputDirectorySelectCommand.Subscribe(OnSelectVDBExportDirectory);
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

        private void OnSelectVDBExportDirectory()
        {
            var dialog = new Microsoft.WindowsAPICodePack.Dialogs.CommonOpenFileDialog();
            dialog.IsFolderPicker = true;
            var result = dialog.ShowDialog();
            if (result == Microsoft.WindowsAPICodePack.Dialogs.CommonFileDialogResult.Ok)
            {
                this.VDBOutputDirectoryPath.Value = dialog.FileName;
            }
        }

        private void OnStart()
        {
            var files = System.IO.Directory.GetFiles(this.VDBInputDirectoryPath.Value, "*.vdb");
            foreach(var file in files)
            {
                var pointIds = vdb.Read(file, world);
                var volumeIds = new List<int>();
                foreach(int id in pointIds) {
                    if (vdb.GetVDBType(id, world) != VDBModel.VDBType.Point)
                    {
                        continue;
                    }
                    int volumeId = vdb.CreateVDBVolume(world, "Volume", false);
                    vdb.ConvertPSToVolume(id, volumeId, world, Threshold.Value);
                    volumeIds.Add(volumeId);
                }
                var newName = System.IO.Path.Combine( this.VDBOutputDirectoryPath.Value, "volume_" + System.IO.Path.GetFileName(file));
                vdb.Write(newName, world, new List<int>(), volumeIds);
                foreach (int id in pointIds)
                {
                    world.Delete(id);
                }
                foreach (int id in volumeIds)
                {
                    world.Delete(id);
                }
            }
        }
    }
}
