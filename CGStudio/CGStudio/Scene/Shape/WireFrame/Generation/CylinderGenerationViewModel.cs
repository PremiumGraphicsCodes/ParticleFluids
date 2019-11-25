﻿using PG.Core.Shape;
using Reactive.Bindings;
using PG.Control.Math;
using Prism.Mvvm;

namespace PG.CGStudio.Generation.WireFrame
{
    public class CylinderGenerationViewModel : BindableBase
    {
        public Cylinder3dViewModel CylinderViewModel { get; }
            = new Cylinder3dViewModel();

        public ReactiveProperty<int> UNum { get; }
            = new ReactiveProperty<int>(36);

        public AppearanceViewModel AppearanceViewModel { get; }
            = new AppearanceViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public CylinderGenerationViewModel()
        {
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new WireFrameBuilder();
            var cylinder = CylinderViewModel.Value;
            builder.Add(cylinder, this.UNum.Value);
            var wireFrame = builder.Build();
            MainModel.Instance.World.Scenes.AddWireFrameScene(wireFrame, "WFCylinder", AppearanceViewModel.Value);
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
        }
    }
}
