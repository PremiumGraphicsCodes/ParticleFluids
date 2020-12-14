using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Math;
using PG.Core.Shape;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;
using System.Collections.Generic;

namespace FluidStudio.Scene.PolygonMesh
{
    public class BoxGenerationViewModel : BindableBase
    {
        public ReactiveProperty<int> Count { get; }
            = new ReactiveProperty<int>(10000);

        public Box3dViewModel BoxViewModel { get; }
            = new Box3dViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<double> Dx { get; }
            = new ReactiveProperty<double>(1.0);

        public ReactiveProperty<double> Dy { get; }
            = new ReactiveProperty<double>(1.0);

        public ReactiveProperty<double> Dz { get; }
            = new ReactiveProperty<double>(1.0);

        public BoxGenerationViewModel(SceneList world, Canvas3d canvas)
        {
            BoxViewModel.Value = new Box3d(new Vector3d(0, 0, 0), new Vector3d(10, 10, 10));
            this.GenerationCommand.Subscribe(() => OnGenerate(world, canvas));
        }

        private void OnGenerate(SceneList world, Canvas3d canvas)
        {
            var positions = new List<Vector3d>();
            var box = BoxViewModel.Value;

            var builder = new PolygonMeshBuilder();
            builder.Add(box);
            var newId = world.AddPolygonMeshScene(builder.ToPolygonMesh(), "PSMesh", 1);
            canvas.Camera.Fit();
            canvas.BuildShader(world, newId);
            canvas.Render();
        }
    }
}
