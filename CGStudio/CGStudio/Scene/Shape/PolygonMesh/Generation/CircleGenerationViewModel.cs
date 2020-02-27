using PG.Control.Math;
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

        public CircleGenerationViewModel()
        {
            GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new PolygonMeshBuilder();
            builder.Add(CircleViewModel.Value, UNum.Value);

            World.Instance.Scenes.AddPolygonMeshScene(builder.ToPolygonMesh(), "PMCircle", 1);
            World.Instance.Scenes.Sync();
            World.Instance.Camera.Fit();

            Canvas3d.Instance.Update(World.Instance);
            Canvas3d.Instance.Render();
        }
    }
}
