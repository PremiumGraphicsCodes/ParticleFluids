﻿using PG.Control.Math;
using PG.Core.Shape;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.WireFrame
{
    public class SphereGenerationViewModel : BindableBase
    {
        public ReactiveProperty<int> UNum { get; }
            = new ReactiveProperty<int>(36);

        public ReactiveProperty<int> VNum { get; }
            = new ReactiveProperty<int>(36);

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public Sphere3dViewModel SphereViewModel { get; }
            = new Sphere3dViewModel();

        public AppearanceViewModel AppearanceViewModel { get; }
            = new AppearanceViewModel();

        public SphereGenerationViewModel()
        {
            this.GenerationCommand.Subscribe(OnExecute);
        }

        private void OnExecute()
        {
            var builder = new WireFrameBuilder();
            builder.Add(SphereViewModel.Value, UNum.Value, VNum.Value);

            World.Instance.Scenes.AddWireFrameScene(builder.ToWireFrame(), "WFSphere", AppearanceViewModel.Value, 1);
            World.Instance.Camera.Fit();

            Canvas3d.Instance.Update(World.Instance);
            Canvas3d.Instance.Render();
        }
    }
}
