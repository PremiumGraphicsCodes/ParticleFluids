using PG.Core.Shape;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.WireFrame
{
    public class BoxGenerationViewModel
    {
        public PG.Control.Box3dViewModel BoxViewModel { get; private set; }

        public ReactiveCommand GenerationCommand { get; private set; }

        public BoxGenerationViewModel()
        {
            this.BoxViewModel = new Control.Box3dViewModel();
            this.GenerationCommand = new ReactiveCommand();
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new WireFrameBuilder();
            var box = BoxViewModel.Box;
            builder.Build(box);
        }
    }
}
