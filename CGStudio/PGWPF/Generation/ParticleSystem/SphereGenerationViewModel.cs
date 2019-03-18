using PG.Core.Math;
using Prism.Mvvm;
using System.Collections.Generic;
using PG.Control;
using Reactive.Bindings;
using PG.Control.Math;
using PG.Control.Graphics;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class SphereGenerationViewModel : BindableBase
    {
        public ReactiveCommand GenerationCommand { get; }

        public ReactiveProperty<int> Count { get; }

        public Sphere3dViewModel SphereViewModel { get; }

        public ColorRGBAViewModel ColorViewModel { get; }

        public SphereGenerationViewModel()
        {
            this.SphereViewModel = new Sphere3dViewModel();
            this.ColorViewModel = new ColorRGBAViewModel();
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
                var u = random.NextDouble();
                var v = random.NextDouble();
                var pos = SphereViewModel.Value.GetPosition(u,v);
                positions.Add(pos);
            }
            var particles = new PG.Core.Shape.ParticleSystem(positions);
            Repository.Instance.Objects.Add(particles, ColorViewModel.Value, 1.0f);
            OpenGLPresenter.Instance.Update(Repository.Instance);
            OpenGLPresenter.Instance.Render();
        }
    }
}
