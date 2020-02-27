using PG.Control.Math;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Shape.ParticleSystem.Generation
{
    public class ConeGenerationViewModel
    {
        public Cone3dViewModel ConeViewModel { get; }
            = new Cone3dViewModel();

        public ReactiveProperty<int> Count { get; }
            = new ReactiveProperty<int>(10000);

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public ConeGenerationViewModel()
        {
            GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var cone = ConeViewModel.Value;
        }
    }
}
