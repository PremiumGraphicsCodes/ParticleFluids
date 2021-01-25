using FluidStudio.VDB;
using PG.Control.OpenGL;
using PG.Control.UI;
using PG.Core.Math;
using PG.Scene;
using Reactive.Bindings;
using System.Collections.Generic;

namespace FluidStudio.Tool.Modeling
{
    public class VolumeToPSViewModel
    {
        public SceneSelectViewModel VolumeSelectViewModel { get; }

        public ReactiveCommand ConvertCommand { get; }
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
            ConvertCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var volumeId = VolumeSelectViewModel.Id.Value;

            var psId = vdb.CreateVDBPoints(world, new List<Vector3d>(), "ConvertedPoints");
            this.canvas.BuildShader(world, psId);

            this.vdb.ConvertVolumeToPS(volumeId, psId, world);
            this.canvas.SendShader(world, psId);
        }
    }
}
