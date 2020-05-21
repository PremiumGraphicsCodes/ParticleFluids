using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Shape;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.PolygonMesh
{
    public class BoxGenerationViewModel
    {
        public Box3dViewModel BoxViewModel { get; }
            = new Box3dViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        private readonly Canvas3d canvas;

        public BoxGenerationViewModel(Canvas3d canvas)
        {
            this.canvas = canvas;
            GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new PolygonMeshBuilder();
            var box = BoxViewModel.Value;
            builder.Add(box);

            World.Instance.Scenes.AddPolygonMeshScene(builder.ToPolygonMesh(), "PMBox", 1);
            World.Instance.Scenes.Sync();
            canvas.Camera.Fit();

            canvas.Update(World.Instance);
            canvas.Render();
        }
    }
}
