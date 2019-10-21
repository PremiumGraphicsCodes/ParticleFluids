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

        public Box3dViewModel BoxViewModel { get; }

        public ReactiveCommand GenerationCommand { get; }

        public AppearanceViewModel Appearance { get; }

        public BoxGenerationViewModel()
        {
            this.BoxViewModel = new Box3dViewModel();
            this.Appearance = new AppearanceViewModel();
            this.Count = new ReactiveProperty<int>(10000);
            this.GenerationCommand = new ReactiveCommand();
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
            MainModel.Instance.Repository.AddParticleSystemScene(positions, "PSBox", false, 1.0f, new Core.Graphics.ColorRGBA(1.0f, 1.0f, 1.0f,1.0f));//, Appearance.Value, "PSBox");
            Canvas3d.Instance.Update(MainModel.Instance.Repository);
            Canvas3d.Instance.Render();
        }
    }
}
