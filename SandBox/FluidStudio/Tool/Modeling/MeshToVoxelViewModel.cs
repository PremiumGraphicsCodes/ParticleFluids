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
    class MeshToVoxelViewModel
    {
        public SceneSelectViewModel MeshSelectViewModel { get; }

        public ReactiveCommand ConvertCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<double> DivideLength { get; }
            = new ReactiveProperty<double>(1.0);

        private MainModel mainModel;

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        public MeshToVoxelViewModel(MainModel mainModel, SceneList scenes, Canvas3d canvas)
        {
            this.mainModel = mainModel;
            this.world = scenes;
            this.canvas = canvas;
            this.MeshSelectViewModel = new SceneSelectViewModel(scenes, canvas);
            this.ConvertCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var meshId = MeshSelectViewModel.Id.Value;
            var divideLength = DivideLength.Value;

            var voxelId = mainModel.SpaceModel.CreateVoxel("VDBVolume", 1);
            this.canvas.BuildShader(world, voxelId);

            this.mainModel.SpaceModel.PolygonToVoxel(meshId, voxelId, divideLength);
            this.canvas.SendShader(world, voxelId);
        }
    }
}
