using PG.Control.Math;
using PG.Control.OpenGL;
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

        public ConeGenerationViewModel(World world, Canvas3d canvas)
        {
            GenerationCommand.Subscribe(() => OnGenerate(world, canvas));
        }

        private void OnGenerate(World world, Canvas3d canvas)
        {
            var cone = ConeViewModel.Value;
        }
    }
}
