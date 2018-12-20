using PG.Control;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class CylinderGenerationViewModel : BindableBase
    {
        public ReactiveProperty<int> Count { get; }

        public Cylinder3dViewModel CylinderViewModel { get; }

        public ReactiveCommand GenerationCommand { get; }

        public CylinderGenerationViewModel()
        {
            this.Count = new ReactiveProperty<int>(10000);
            this.CylinderViewModel = new Cylinder3dViewModel();
            this.GenerationCommand = new ReactiveCommand();
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            ;
        }
    }
}
