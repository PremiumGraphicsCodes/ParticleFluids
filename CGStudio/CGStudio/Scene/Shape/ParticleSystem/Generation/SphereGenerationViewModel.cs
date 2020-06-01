using PG.Core.Math;
using Prism.Mvvm;
using System.Collections.Generic;
using Reactive.Bindings;
using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Scene;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class SphereGenerationViewModel : BindableBase
    {
        public ReactiveProperty<int> Count { get; }
            = new ReactiveProperty<int>(10000);

        public Sphere3dViewModel SphereViewModel { get; }
            = new Sphere3dViewModel();

        public AppearanceViewModel Appearance { get; }
            = new AppearanceViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public SphereGenerationViewModel(SceneList world, Canvas3d canvas)
        {
            this.GenerationCommand.Subscribe(() => OnGenerate(world, canvas));
        }

        private void OnGenerate(SceneList world, Canvas3d canvas)
        {
            var random = new System.Random();
            var positions = new List<Vector3d>();
            var sphere = SphereViewModel.Value;
            for (int i = 0; i < Count.Value; ++i) {
                var u = random.NextDouble();
                var v = random.NextDouble();
                var pos = sphere.GetPosition(1.0,u,v);
                positions.Add(pos);
            }
            var id = world.AddParticleSystemScene(positions, "PSSphere", Appearance.Value, 1);
            canvas.Camera.Fit();
            canvas.BuildShader(world, id);
            canvas.Render();
        }
    }
}
