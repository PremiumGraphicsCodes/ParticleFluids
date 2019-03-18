using PG.Control;
using PG.Control.Graphics;
using PG.Control.Math;
using PG.Core.Math;
using PG.Core.UI;
using Prism.Mvvm;
using Reactive.Bindings;
using System.Collections.Generic;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class CylinderGenerationViewModel : BindableBase
    {
        public ReactiveProperty<int> Count { get; }
            = new ReactiveProperty<int>();

        public Cylinder3dViewModel CylinderViewModel { get; }
            = new Cylinder3dViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public ColorRGBAViewModel ColorViewModel { get; }

        public CylinderGenerationViewModel()
        {
            this.ColorViewModel = new ColorRGBAViewModel();
            this.Count.Value = 10000;
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var random = new System.Random();
            var positions = new List<Vector3d>();
            var cylinder = CylinderViewModel.Value;
            for (int i = 0; i < Count.Value; ++i)
            {
                var u = random.NextDouble();
                var v = random.NextDouble();
                var pos = cylinder.GetPosition(u, v);
                positions.Add(pos);
            }
            var particles = new PG.Core.Shape.ParticleSystem(positions);
            var a = new ParticleAppearance
            {
                Color = ColorViewModel.Value,
                Size = 1.0f
            };
            Repository.Instance.Objects.Add(particles, a);
            OpenGLPresenter.Instance.Update(Repository.Instance);
            OpenGLPresenter.Instance.Render();
        }
    }
}
