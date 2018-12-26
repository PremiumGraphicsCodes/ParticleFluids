using PG.Control;
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
            builder.Build(box);
            var polygonMesh = builder.PolygonMesh;
            MainModel.Instance.Add(polygonMesh);
        }
    }
}
