using PG.Control.Math;
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

        public BoxGenerationViewModel()
        {
            GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new PolygonMeshBuilder();
            var box = BoxViewModel.Value;
            builder.Add(box);

            World.Instance.Scenes.AddPolygonMeshScene(builder.ToPolygonMesh(), "PMBox", 1);
            World.Instance.Scenes.Sync();
            World.Instance.Camera.Fit();

            Canvas3d.Instance.Update(World.Instance);
            Canvas3d.Instance.Render();
        }
    }
}
