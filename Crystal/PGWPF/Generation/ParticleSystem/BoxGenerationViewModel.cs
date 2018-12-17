using PG.Control;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class BoxGenerationViewModel : BindableBase
    {
        public ReactiveProperty<int> Count { get; private set; }

        public Box3dViewModel BoxViewModel { get; private set; }

        public BoxGenerationViewModel()
        {
            this.BoxViewModel = new Box3dViewModel();
            this.Count = new ReactiveProperty<int>(10000);
        }
    }
}
