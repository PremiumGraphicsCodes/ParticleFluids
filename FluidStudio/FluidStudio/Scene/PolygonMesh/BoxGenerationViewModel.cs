using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Math;
using PG.Core.Shape;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;

namespace FluidStudio.Scene.PolygonMesh
{
    public class BoxGenerationViewModel : BindableBase
    {
        public Box3dViewModel BoxViewModel { get; }
            = new Box3dViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public BoxGenerationViewModel(SceneList world, Canvas3d canvas)
        {
            this.BoxViewModel.Value = new Box3d(new Vector3d(0, 0, 0), new Vector3d(10, 10, 10));
            this.GenerationCommand.Subscribe(() => OnGenerate(world, canvas));
        }

        private void OnGenerate(SceneList world, Canvas3d canvas)
        {
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
