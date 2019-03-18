using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.WireFrame
{
    public class WireFrameGenerationViewModel : BindableBase
    {
        public ReactiveProperty<BindableBase> ContentViewModel { get; }
            = new ReactiveProperty<BindableBase>();

        public WireFrameGenerationViewModel()
        {
            this.ContentViewModel.Value = new SphereGenerationViewModel();
        }
    }
}
