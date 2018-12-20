using PG.Core.Shape;
using Reactive.Bindings;
using PG.Control;

namespace PG.CGStudio.Generation.WireFrame
{
    public class BoxGenerationViewModel
    {
        public Box3dViewModel BoxViewModel { get; }

        public ReactiveCommand GenerationCommand { get; }

        public BoxGenerationViewModel()
        {
            this.BoxViewModel = new Box3dViewModel();
            this.GenerationCommand = new ReactiveCommand();
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new WireFrameBuilder();
            var box = BoxViewModel.Box;
            builder.Build(box);
            var wireFrame = builder.WireFrame;
            MainModel.Instance.Add(wireFrame);
            Canvas3dView.Instance.Update(MainModel.Instance);
            Canvas3dView.Instance.Render();
        }
    }
}
