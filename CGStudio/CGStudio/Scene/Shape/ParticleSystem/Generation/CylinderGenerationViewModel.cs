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
            = new ReactiveProperty<int>(10000);

        public Cylinder3dViewModel CylinderViewModel { get; }
            = new Cylinder3dViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public AppearanceViewModel Appearance { get; }
            = new AppearanceViewModel();

        public CylinderGenerationViewModel(World world)
        {
            this.GenerationCommand.Subscribe(() => OnGenerate(world));
        }

        private void OnGenerate(World world)
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
            var newId = world.Scenes.AddParticleSystemScene(positions, "PSCylinder", Appearance.Value, 1);//, Appearance.Value, "PSCylinder");
            world.Camera.Fit();

            HwndHostPresenter3d.Instance.BuildShader(world, newId);
            HwndHostPresenter3d.Instance.Render();
        }
    }
}
