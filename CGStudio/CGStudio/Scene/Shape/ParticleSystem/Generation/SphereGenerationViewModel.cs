﻿using PG.Core.Math;
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
                var pos = sphere.GetPosition(1.0,u,v);
                positions.Add(pos);
            }
            World.Instance.Scenes.AddParticleSystemScene(positions, "PSSphere", Appearance.Value, 1);//, Appearance.Value, "PSBox");

            //MainModel.Instance.Repository.Objects.Add(particles, Appearance.Value, "PSSphere");
            Canvas3d.Instance.Update(World.Instance);
            Canvas3d.Instance.Render();
        }
    }
}
