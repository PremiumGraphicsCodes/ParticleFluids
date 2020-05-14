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

        public ConeGenerationViewModel(World world)
        {
            GenerationCommand.Subscribe(() => OnGenerate(world));
        }

        private void OnGenerate(World world)
        {
            var cone = ConeViewModel.Value;
        }
    }
}
