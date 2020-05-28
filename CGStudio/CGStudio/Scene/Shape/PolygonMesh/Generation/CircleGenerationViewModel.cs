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

        private readonly World world;

        private readonly Canvas3d canvas;

        public CircleGenerationViewModel(World world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new PolygonMeshBuilder();
            builder.Add(CircleViewModel.Value, UNum.Value);

            var newId = world.Scenes.AddPolygonMeshScene(builder.ToPolygonMesh(), "PMCircle", 1);

            canvas.Camera.Fit();
            canvas.BuildShader(world, newId);
            canvas.Render();
        }
    }
}
