using PG.Control;
using PG.Core.Shape;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.WireFrame
{
    public class SphereGenerationViewModel
    {
        public ReactiveProperty<int> UNum { get; }
            = new ReactiveProperty<int>();

        public ReactiveProperty<int> VNum { get; }
            = new ReactiveProperty<int>();

        public ReactiveCommand ExecuteCommand { get; }
            = new ReactiveCommand();

        public Sphere3dViewModel SphereViewModel { get; }
            = new Sphere3dViewModel();

        public SphereGenerationViewModel()
        {
            this.UNum.Value = 24;
            this.VNum.Value = 24;
            this.ExecuteCommand.Subscribe(OnExecute);
        }

        private void OnExecute()
        {
            var builder = new WireFrameBuilder();
            builder.Build(SphereViewModel.Value, UNum.Value, VNum.Value);
            Repository.Instance.Objects.Add(builder.WireFrame);
            OpenGLPresenter.Instance.Update(Repository.Instance);
            OpenGLPresenter.Instance.Render();
        }
    }
}
