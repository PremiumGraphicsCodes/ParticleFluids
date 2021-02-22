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

        public ReactiveCommand ConvertCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<double> DivideLength { get; }
            = new ReactiveProperty<double>(1.0);

        private readonly VDBModel vdb;

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        public MeshToVolumeViewModel(MainModel mainModel, SceneList scenes, Canvas3d canvas)
        {
            this.vdb = mainModel.VDBModel;
            this.world = scenes;
            this.canvas = canvas;
            this.MeshSelectViewModel = new SceneSelectViewModel(scenes, canvas);
            this.ConvertCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var meshId = MeshSelectViewModel.Id.Value;
            var divideLength = DivideLength.Value;

            var volumeId = vdb.CreateVDBVolume(world, "VDBVolume", true);
            this.canvas.BuildShader(world, volumeId);

            this.vdb.ConvertMeshToVolume(meshId, volumeId, divideLength, world);
            this.canvas.SendShader(world, volumeId);
        }
    }
}
