using FluidStudio.Physics;
using FluidStudio.VDB;
using PG.Scene;
using Reactive.Bindings;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

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

        public ReactiveProperty<float> ParticleRadius { get; }
            = new ReactiveProperty<float>(0.5f);

        public ReactiveProperty<float> CellLength { get; }
            = new ReactiveProperty<float>(1.0f);

        public ReactiveProperty<float> Threshold { get; }
            = new ReactiveProperty<float>(2.0f);

        public ReactiveCommand StartCommand { get; }
            = new ReactiveCommand();

        private readonly SceneList world;

        private readonly VDBModel vdb;

        private readonly MainModel mainModel;

        public PSToVolumeViewModel(MainModel mainModel)
        {
            this.world = mainModel.Scenes;
            this.vdb = mainModel.VDBModel;
            this.mainModel = mainModel;
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

        private ProgressView progressView;
        private ProgressViewModel progressVM;

        private async void OnStart()
        {
            progressView = new ProgressView();
            progressVM = new ProgressViewModel();
            progressView.DataContext = progressVM;
            var files = System.IO.Directory.GetFiles(this.VDBInputDirectoryPath.Value, "*.vdb");
            progressVM.Min.Value = 0;
            progressVM.Max.Value = files.Count();
            progressVM.Value.Value = 50;
            progressView.Show();
            foreach (var file in files)
            {
                await Task.Run(() => Execute(file));
            }
        }

        private void Execute(string file)
        {
            var pointIds = vdb.Read(file, ParticleRadius.Value);
            var volumeIds = new List<int>();
            foreach (int id in pointIds)
            {
                if (vdb.GetVDBType(id, world) != VDBModel.VDBType.Point)
                {
                    continue;
                }
                int volumeId = vdb.CreateVDBVolume("Volume", false);
                vdb.ConvertPSToVolume(id, volumeId, Threshold.Value);
                volumeIds.Add(volumeId);
            }
            var newName = System.IO.Path.Combine(this.VDBOutputDirectoryPath.Value, "volume_" + System.IO.Path.GetFileName(file));
            vdb.Write(newName, new List<int>(), volumeIds);
            foreach (int id in pointIds)
            {
                world.Delete(id);
            }
            foreach (int id in volumeIds)
            {
                world.Delete(id);
            }
            var value = progressVM.Value.Value;
            progressVM.Value.Value = value + 1;
        }

        private void ExecuteSmooth(string file)
        {
            var pointIds = vdb.Read(file, ParticleRadius.Value);
            var volumeIds = new List<int>();
            foreach (int id in pointIds)
            {
                if (vdb.GetVDBType(id, world) != VDBModel.VDBType.Point)
                {
                    continue;
                }
                var resolution = new int[3];
                resolution[0] = 2;
                resolution[1] = 2;
                resolution[2] = 2;
                int sparseVolumeId = mainModel.SpaceModel.CreateSparseVolume("SparseVolume", resolution, new PG.Core.Math.Box3d(), 1);
                volumeIds.Add(sparseVolumeId);
                mainModel.PhysicsModel.ToSmoothVolume(world, id, sparseVolumeId, ParticleRadius.Value, 2.0f);
            }
            foreach (int id in pointIds)
            {
                world.Delete(id);
            }
            foreach (int id in volumeIds)
            {
                world.Delete(id);
            }
            var value = progressVM.Value.Value;
            progressVM.Value.Value = value + 1;

            //            volumeIds = 
        }
    }
}
