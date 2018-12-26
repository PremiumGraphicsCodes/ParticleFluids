using PG.Core.Math;
using Prism.Mvvm;
using System.Collections.Generic;
using PG.Control;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class SphereGenerationViewModel : BindableBase
    {
        public ReactiveCommand GenerationCommand { get; }

        public ReactiveProperty<int> Count { get; }

        public Sphere3dViewModel SphereViewModel { get; }

        public SphereGenerationViewModel()
        {
            this.SphereViewModel = new Sphere3dViewModel();
            this.Count = new ReactiveProperty<int>();
            this.Count.Value = 10000;
            this.GenerationCommand = new ReactiveCommand();
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var random = new System.Random();
            var positions = new List<Vector3d>();
            var sphere = SphereViewModel.Value;
            for (int i = 0; i < Count.Value; ++i) {
                var theta = random.NextDouble() * 2.0 * System.Math.PI;
                var phi = random.NextDouble() * System.Math.PI;
                var pos = SphereViewModel.Value.GetPositionByAngle(theta, phi);
                positions.Add(pos);
            }
            var particles = new PG.Core.Shape.ParticleSystem(positions);
            MainModel.Instance.Add(particles);
            Canvas3dView.Instance.Update(MainModel.Instance);
            Canvas3dView.Instance.Render();
        }
    }
}
