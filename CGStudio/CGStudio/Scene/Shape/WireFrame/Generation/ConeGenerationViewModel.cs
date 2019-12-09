﻿using PG.Control.Math;
using PG.Core.Shape;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.WireFrame
{
    public class ConeGenerationViewModel
    {
        public Cone3dViewModel ConeViewModel { get; }

        public AppearanceViewModel AppearanceViewModel { get; }

        public ReactiveCommand GenerationCommand { get; }

        public ConeGenerationViewModel()
        {
            this.ConeViewModel = new Cone3dViewModel();
            this.AppearanceViewModel = new AppearanceViewModel();
            this.GenerationCommand = new ReactiveCommand();
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new WireFrameBuilder();
            var cone = ConeViewModel.Value;
            builder.Add(cone, 24);
            var wireFrame = builder.ToWireFrame();
            var appearance = AppearanceViewModel.Value;
            MainModel.Instance.World.Scenes.AddWireFrameScene(wireFrame, "WFCone", appearance, 1);
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
        }

    }
}
