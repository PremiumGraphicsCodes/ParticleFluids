using PG.CGStudio.Generation.ParticleSystem;
using PG.Control.Math;
using PG.Core.Math;
using Reactive.Bindings;
using System.Collections.Generic;

namespace PG.CGStudio.Scene.Shape.ParticleSystem.Generation
{
    public class CircleGenerationViewModel
    {
        public Circle3dViewModel CircleViewModel { get; }
            = new Circle3dViewModel();

        public ReactiveProperty<int> Count { get; }
            = new ReactiveProperty<int>(1000);

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public AppearanceViewModel AppearanceViewModel { get; }
            = new AppearanceViewModel();

        public CircleGenerationViewModel()
        {
            GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var random = new System.Random();
            var positions = new List<Vector3d>();
            var circle = CircleViewModel.Value;
            for (int i = 0; i < Count.Value; ++i)
            {
                var u = random.NextDouble();
                var pos = circle.GetPosition(u);
                positions.Add(pos);
            }
            World.Instance.Scenes.AddParticleSystemScene(positions, "PSCircle", AppearanceViewModel.Value, 1);
            World.Instance.Scenes.Sync();
            World.Instance.Camera.Fit();

            Canvas3d.Instance.Update(World.Instance);
            Canvas3d.Instance.Render();
        }
    }
}
