using PG.Control;
using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Shape;
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

        private World world;

        private Canvas3d canvas;

        public SphereGenerationViewModel(World world, Canvas3d canvas)
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

            world.Scenes.AddPolygonMeshScene(builder.ToPolygonMesh(), "PMSphere", 1);
            world.Scenes.Sync();

            canvas.Camera.Fit();
            canvas.Update(World.Instance);
            canvas.Render();
        }
    }
}
