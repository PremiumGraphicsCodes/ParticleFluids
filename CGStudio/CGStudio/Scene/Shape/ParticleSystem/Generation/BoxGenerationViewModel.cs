using PG.Core.Math;
using Prism.Mvvm;
using Reactive.Bindings;
using System.Collections.Generic;
using PG.Control.Math;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class BoxGenerationViewModel : BindableBase
    {
        public ReactiveProperty<int> Count { get; }
            = new ReactiveProperty<int>(10000);

        public Box3dViewModel BoxViewModel { get; }
            = new Box3dViewModel();

        public AppearanceViewModel Appearance { get; }
            = new AppearanceViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public BoxGenerationViewModel()
        {
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
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
            World.Instance.Scenes.AddParticleSystemScene(positions, "PSBox", Appearance.Value, 1);
            World.Instance.Scenes.Sync();
            World.Instance.Camera.Fit();

            Canvas3d.Instance.Update(World.Instance);
            Canvas3d.Instance.Render();
        }
    }
}
