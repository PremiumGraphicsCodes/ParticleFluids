using FluidStudio.VDB;
using PG.Control.OpenGL;
using PG.Control.UI;
using PG.Scene;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.Tool.Modeling
{
    public class VolumeToPSViewModel
    {
        public SceneSelectViewModel VolumeSelectViewModel { get; }

        public SceneSelectViewModel PSSelectViewModel { get; }

        public ReactiveCommand GenerateCommand { get; }
            = new ReactiveCommand();

        private readonly VDBModel vdb;

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        public VolumeToPSViewModel(MainModel mainModel, SceneList scenes, Canvas3d canvas)
        {
            this.vdb = mainModel.VDBModel;
            this.world = scenes;
            this.canvas = canvas;
            VolumeSelectViewModel = new SceneSelectViewModel(scenes, canvas);
            PSSelectViewModel = new SceneSelectViewModel(scenes, canvas);
            GenerateCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var volumeId = VolumeSelectViewModel.Id.Value;
            var psId = PSSelectViewModel.Id.Value;
            this.vdb.ConvertVolumeToPS(volumeId, psId, world);
            this.canvas.SendShader(world, psId);
        }
    }
}
