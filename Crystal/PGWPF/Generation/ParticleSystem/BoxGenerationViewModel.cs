using PG.Control;
using PG.Core.Math;
using Prism.Mvvm;
using Reactive.Bindings;
using System.Collections.Generic;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class BoxGenerationViewModel : BindableBase
    {
        public ReactiveProperty<int> Count { get; }

        public Box3dViewModel BoxViewModel { get; }

        public ReactiveCommand GenerationCommand { get; }

        public BoxGenerationViewModel()
        {
            this.BoxViewModel = new Box3dViewModel();
            this.Count = new ReactiveProperty<int>(10000);
            this.GenerationCommand = new ReactiveCommand();
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var random = new System.Random();
            var positions = new List<Vector3d>();
            var box = BoxViewModel.Box;
            for (int i = 0; i < Count.Value; ++i)
            {
                var u = random.NextDouble();
                var v = random.NextDouble();
                var w = random.NextDouble();
                var pos = box.GetPosition(u, v, w);
                positions.Add(pos);
            }
            var particles = new PG.Core.Shape.ParticleSystem(positions);
            MainModel.Instance.Add(particles);
            Canvas3dView.Instance.Update(MainModel.Instance);
            Canvas3dView.Instance.Render();
        }
    }
}
