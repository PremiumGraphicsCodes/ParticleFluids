using PG.Control.Math;
using PG.Core.Shape;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.PolygonMesh
{
    public class BoxGenerationViewModel
    {
        public Box3dViewModel BoxViewModel { get; }

        public ReactiveCommand GenerationCommand { get; }

        public BoxGenerationViewModel()
        {
            BoxViewModel = new Box3dViewModel();
            GenerationCommand = new ReactiveCommand();
            GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new PolygonMeshBuilder();
            var box = BoxViewModel.Value;
            builder.Add(box);
            World.Instance.Scenes.AddPolygonMeshScene(builder.ToPolygonMesh(), "PMBox", 1);
            Canvas3d.Instance.Update(World.Instance);
            Canvas3d.Instance.Render();
        }
    }
}
