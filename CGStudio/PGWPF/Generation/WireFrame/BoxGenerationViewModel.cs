using PG.Core.Shape;
using Reactive.Bindings;
using PG.Control;

namespace PG.CGStudio.Generation.WireFrame
{
    public class BoxGenerationViewModel
    {
        public Box3dViewModel BoxViewModel { get; }
            = new Box3dViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public BoxGenerationViewModel()
        {
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new WireFrameBuilder();
            var box = BoxViewModel.Value;
            builder.Build(box);
            var wireFrame = builder.WireFrame;
            MainModel.Instance.Add(wireFrame);
            Canvas3dView.Instance.Update(MainModel.Instance);
            Canvas3dView.Instance.Render();
        }
    }
}
