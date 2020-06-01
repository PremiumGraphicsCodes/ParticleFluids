using PG.Control;
using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Shape;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.PolygonMesh
{
    public class SphereGenerationViewModel : BindableBase
    {
        public ReactiveProperty<int> UNum { get; }
            = new ReactiveProperty<int>();

        public ReactiveProperty<int> VNum { get; }
            = new ReactiveProperty<int>();

        public ReactiveCommand GenerateCommand { get; }
            = new ReactiveCommand();

        public Sphere3dViewModel SphereViewModel { get; }
            = new Sphere3dViewModel();

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        public SphereGenerationViewModel(SceneList world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            this.UNum.Value = 24;
            this.VNum.Value = 24;
            this.GenerateCommand.Subscribe(OnExecute);
        }
  
        private void OnExecute()
        {
            var builder = new PolygonMeshBuilder();
            builder.Add(SphereViewModel.Value, UNum.Value, VNum.Value);

            var newId = world.AddPolygonMeshScene(builder.ToPolygonMesh(), "PMSphere", 1);

            canvas.Camera.Fit();
            canvas.BuildShader(world, newId);
            canvas.Render();
        }
    }
}
