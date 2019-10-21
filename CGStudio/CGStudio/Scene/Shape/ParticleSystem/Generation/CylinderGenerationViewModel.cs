using PG.Control.Math;
using PG.Core.Math;
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

        public AppearanceViewModel Appearance { get; }

        public CylinderGenerationViewModel()
        {
            this.Appearance = new AppearanceViewModel();
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
                var pos = cylinder.GetPosition(1.0, u, v);
                positions.Add(pos);
            }
            var particles = new PG.Core.Shape.ParticleSystem(positions);
            MainModel.Instance.Repository.AddParticleSystemScene(positions, "PSCylinder", false, Appearance.Value);//, Appearance.Value, "PSCylinder");
            Canvas3d.Instance.Update(MainModel.Instance.Repository);
            Canvas3d.Instance.Render();
        }
    }
}
