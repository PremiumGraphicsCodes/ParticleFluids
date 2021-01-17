using FluidStudio.VDB;
using PG.Control.OpenGL;
using PG.Control.UI;
using PG.Scene;
using Reactive.Bindings;

namespace FluidStudio.Tool.Modeling
{
    public class MeshToVolumeViewModel
    {
        public SceneSelectViewModel MeshSelectViewModel { get; }

        public SceneSelectViewModel VolumeSelectViewModel { get; }

        public ReactiveCommand GenerateCommand { get; }
            = new ReactiveCommand();

        private readonly VDBModel vdb;

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        public MeshToVolumeViewModel(MainModel mainModel, SceneList scenes, Canvas3d canvas)
        {
            this.vdb = mainModel.VDBModel;
            this.world = scenes;
            this.canvas = canvas;
            this.MeshSelectViewModel = new SceneSelectViewModel(scenes, canvas);
            this.VolumeSelectViewModel = new SceneSelectViewModel(scenes, canvas);
            this.GenerateCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var meshId = MeshSelectViewModel.Id.Value;
            var volumeId = VolumeSelectViewModel.Id.Value;
            this.vdb.ConvertMeshToVolume(meshId, volumeId, world);
            this.canvas.SendShader(world, volumeId);
        }
    }
}
