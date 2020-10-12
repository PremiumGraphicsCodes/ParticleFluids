using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;

namespace FluidStudio.Scene.ParticleSystem
{
    public class BoxGenerationViewModel : BindableBase
    {
        public ReactiveProperty<int> Count { get; }
            = new ReactiveProperty<int>(10000);

        public Box3dViewModel BoxViewModel { get; }
            = new Box3dViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public BoxGenerationViewModel(SceneList world, Canvas3d canvas)
        {
            this.GenerationCommand.Subscribe(() => OnGenerate(world, canvas));
        }

        private void OnGenerate(SceneList world, Canvas3d canvas)
        {
            /*
            var random = new System.Random();
            var positions = new List<Vector3d>();
            var box = BoxViewModel.Value;
            for (int i = 0; i < Count.Value; ++i)
            {
                var u = random.NextDouble();
                var v = random.NextDouble();
                var w = random.NextDouble();
                var pos = box.GetPosition(u, v, w);
                positions.Add(pos);
            }
            var newId = world.AddParticleSystemScene(positions, "PSBox", Appearance.Value, 1);
            canvas.Camera.Fit();
            canvas.BuildShader(world, newId);
            canvas.Render();
            */
        }
    }
}
