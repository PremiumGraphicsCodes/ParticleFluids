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
            Repository.Instance.Objects.Add(wireFrame);
            OpenGLPresenter.Instance.Update(Repository.Instance);
            OpenGLPresenter.Instance.Render();
        }
    }
}
