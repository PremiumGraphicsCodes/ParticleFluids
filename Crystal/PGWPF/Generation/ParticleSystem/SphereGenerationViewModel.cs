using PG.Core.Math;
using Prism.Mvvm;
using System.Collections.Generic;
using PG.Control;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class SphereGenerationViewModel : BindableBase
    {
        private Sphere3dViewModel sphereViewModel;

        public ReactiveCommand GenerationCommand { get; private set; }

        private int count;

        public Sphere3dViewModel SphereViewModel
        {
            get {return sphereViewModel; }
        }

        public int Count
        {
            get { return count; }
            set { this.SetProperty(ref count, value); }
        }

        public SphereGenerationViewModel()
        {
            this.sphereViewModel = new Sphere3dViewModel();
            this.count = 10000;
            this.GenerationCommand = new ReactiveCommand();
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var random = new System.Random();
            var positions = new List<Vector3d>();
            var sphere = sphereViewModel.Sphere;
            for (int i = 0; i < Count; ++i) {
                var theta = random.NextDouble() * 2.0 * System.Math.PI;
                var phi = random.NextDouble() * System.Math.PI;
                var pos = sphereViewModel.Sphere.GetPositionByAngle(theta, phi);
                positions.Add(pos);
            }
            var particles = new PG.Core.Shape.ParticleSystem(positions);
            MainModel.Instance.Add(particles);
            //var builder = new ParticleSystemBuilder();
            //builder.Build()
        }
    }
}
