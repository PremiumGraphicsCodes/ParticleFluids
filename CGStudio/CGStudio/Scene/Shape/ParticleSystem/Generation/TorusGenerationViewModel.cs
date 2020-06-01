using PG.CGStudio.Generation.ParticleSystem;
using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Shape.ParticleSystem.Generation
{
    public class TorusGenerationViewModel : BindableBase
    {
        public ReactiveProperty<int> Count { get; }
            = new ReactiveProperty<int>(10000);

        public Torus3dViewModel TorusViewModel { get; }
            = new Torus3dViewModel();

        public AppearanceViewModel Appearance { get; }
            = new AppearanceViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        public TorusGenerationViewModel(SceneList world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            /*
            var random = new System.Random();
            var positions = new List<Vector3d>();
            var sphere = SphereViewModel.Value;
            for (int i = 0; i < Count.Value; ++i)
            {
                var u = random.NextDouble();
                var v = random.NextDouble();
                var pos = sphere.GetPosition(1.0, u, v);
                positions.Add(pos);
            }
            var id = world.AddParticleSystemScene(positions, "PSSphere", Appearance.Value, 1);
            canvas.Camera.Fit();
            canvas.BuildShader(world, id);
            canvas.Render();
            */
        }
    }
}
