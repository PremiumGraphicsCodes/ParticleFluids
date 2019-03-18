using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class ParticleSystemGenerationViewModel : BindableBase
    {
        public ReactiveProperty<BindableBase> ContentViewModel { get; }
            = new ReactiveProperty<BindableBase>();

        public ParticleSystemGenerationViewModel()
        {
            this.ContentViewModel.Value = new BoxGenerationViewModel();
        }
    }
}
