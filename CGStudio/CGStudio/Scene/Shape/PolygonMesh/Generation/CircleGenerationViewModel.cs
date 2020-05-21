using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Shape;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Shape.PolygonMesh.Generation
{
    public class CircleGenerationViewModel
    {
        public Circle3dViewModel CircleViewModel { get; }
            = new Circle3dViewModel();

        public ReactiveProperty<int> UNum { get; }
            = new ReactiveProperty<int>(12);

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public CircleGenerationViewModel(World world)
        {
            GenerationCommand.Subscribe(() => OnGenerate(world));
        }

        private void OnGenerate(World world)
        {
            var builder = new PolygonMeshBuilder();
            builder.Add(CircleViewModel.Value, UNum.Value);

            world.Scenes.AddPolygonMeshScene(builder.ToPolygonMesh(), "PMCircle", 1);
            world.Scenes.Sync();
            Canvas3d.Instance.Camera.Fit();

            Canvas3d.Instance.Update(world);
            Canvas3d.Instance.Render();
        }
    }
}
