using FluidStudio.VDB;
using Microsoft.Win32;
using PG.Control.OpenGL;
using PG.Control.UI;
using PG.Scene;
using Reactive.Bindings;
using System.Collections.Generic;

namespace FluidStudio.FileIO
{
    public class ExportViewModel
    {
        public SceneSelectViewModel SceneSelectViewModel { get; }

        public ReactiveProperty<string> FilePath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveCommand FileSelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand ExportCommand { get; }
            = new ReactiveCommand();

        private readonly VDBModel vdb;

        private readonly SceneList scenes;

        public ExportViewModel(MainModel mainModel, SceneList scenes, Canvas3d canvas)
        {
            this.vdb = mainModel.VDBModel;
            this.scenes = scenes;
            SceneSelectViewModel = new SceneSelectViewModel(scenes, canvas);
            FileSelectCommand.Subscribe(OnSelect);
            ExportCommand.Subscribe(OnExport);
        }

        private void OnSelect()
        {
            var dialog = new SaveFileDialog
            {
                Title = "Export",
                Filter = "OpenVDBFile(*.vdb)|*.vdb|AllFiles(*.*)|*.*",
            };
            var isOk = dialog.ShowDialog();
            if(isOk == true)
            {
                this.FilePath.Value = dialog.FileName;
            }
        }

        private void OnExport()
        {
            var path = FilePath.Value;
            var ext = System.IO.Path.GetExtension(path);

            var id = SceneSelectViewModel.Id.Value;
//            if(id == scenes.Scenes[0].SceneType()
            if(ext == ".vdb")
            {
                var pointIds = new List<int>();
                var volumeIds = new List<int>();

                var typeName = scenes.GetSceneTypeName(id);
                if (typeName == "VDBParticleSystem")
                {
                    pointIds.Add(id);
                }
                else if(typeName == "VDBVolume")
                {
                    volumeIds.Add(id);
                }
                var isOk = vdb.Write(path, scenes, pointIds, volumeIds);
            }
        }
    }
}
