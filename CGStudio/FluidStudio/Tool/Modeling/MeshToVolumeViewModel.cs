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

        public ReactiveCommand GenerateCommand { get; }
            = new ReactiveCommand();

        private readonly VDBModel vdb;

        public MeshToVolumeViewModel(MainModel mainModel, SceneList scenes, Canvas3d canvas)
        {
            this.vdb = mainModel.VDBModel;
            this.MeshSelectViewModel = new SceneSelectViewModel(scenes, canvas);
            this.GenerateCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
//            this.vdb.Con
        }
    }
}
