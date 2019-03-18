using PG.CGStudio.Generation.ParticleSystem;
using PG.CGStudio.Generation.WireFrame;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Generation
{
    public class GenerationViewModel : BindableBase
    {
        public GenerationViewModel()
        {
            ContentViewModel.Value = new WireFrameGenerationViewModel();
        }

        public ReactiveProperty<BindableBase> ContentViewModel { get; }
            = new ReactiveProperty<BindableBase>();
    }
}
