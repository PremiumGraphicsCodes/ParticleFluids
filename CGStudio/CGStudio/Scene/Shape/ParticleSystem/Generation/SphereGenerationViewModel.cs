using PG.Core.Math;
using Prism.Mvvm;
using System.Collections.Generic;
using Reactive.Bindings;
using PG.Control.Math;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class SphereGenerationViewModel : BindableBase
    {
        public ReactiveCommand GenerationCommand { get; }

        public ReactiveProperty<int> Count { get; }

        public Sphere3dViewModel SphereViewModel { get; }

        public AppearanceViewModel Appearance { get; }

        public SphereGenerationViewModel()
        {
            this.SphereViewModel = new Sphere3dViewModel();
            this.Count = new ReactiveProperty<int>(10000);
            this.GenerationCommand = new ReactiveCommand();
            this.GenerationCommand.Subscribe(OnGenerate);
            this.Appearance = new AppearanceViewModel();
        }

        private void OnGenerate()
        {
            var random = new System.Random();
            var positions = new List<Vector3d>();
            var sphere = SphereViewModel.Value;
            for (int i = 0; i < Count.Value; ++i) {
                var u = random.NextDouble();
                var v = random.NextDouble();
                var pos = SphereViewModel.Value.GetPosition(1.0,u,v);
                positions.Add(pos);
            }
            var particles = new PG.Core.Shape.ParticleSystem(positions);
            //MainModel.Instance.Repository.AddParticleSystemScene(positions, "PSSphere");
            MainModel.Instance.World.Scenes.AddParticleSystemScene(positions, "PSSphere", Appearance.Value);//, Appearance.Value, "PSBox");

            //MainModel.Instance.Repository.Objects.Add(particles, Appearance.Value, "PSSphere");
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
        }
    }
}
