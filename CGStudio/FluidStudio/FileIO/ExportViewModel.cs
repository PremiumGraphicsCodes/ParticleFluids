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

        public ReactiveCommand ExportCommand { get; }
            = new ReactiveCommand();

        private readonly VDBModel vdb;

        private readonly SceneList scenes;

        public ExportViewModel(MainModel mainModel, SceneList scenes, Canvas3d canvas)
        {
            this.vdb = mainModel.VDBModel;
            this.scenes = scenes;
            SceneSelectViewModel = new SceneSelectViewModel(scenes, canvas);
            ExportCommand.Subscribe(OnSelect);
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
                OnExport(dialog.FileName);
            }
        }

        private void OnExport(string path)
        {
            var ext = System.IO.Path.GetExtension(path);

            var id = SceneSelectViewModel.Id.Value;
//            if(id == scenes.Scenes[0].SceneType()
            if(ext == ".vdb")
            {
                var pointIds = new List<int>();
                var volumeIds = new List<int>();

                var type = vdb.GetVDBType(id, scenes);
                if (VDBModel.VDBType.Point == type)// "VDBParticleSystem")
                {
                    pointIds.Add(id);
                }
                else if(VDBModel.VDBType.Volume == type)
                {
                    volumeIds.Add(id);
                }
                var isOk = vdb.Write(path, scenes, pointIds, volumeIds);
            }
        }
    }
}
