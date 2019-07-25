﻿using PG.Core.Shape;
using Reactive.Bindings;
using PG.Control;
using PG.Control.Math;
using Prism.Mvvm;
using PG.Core.UI;
using PG.Core.Graphics;

namespace PG.CGStudio.Generation.WireFrame
{
    public class CylinderGenerationViewModel : BindableBase
    {
        public Cylinder3dViewModel Cylinder { get; }

        public ReactiveProperty<int> UNum { get; }

        public ReactiveProperty<int> VNum { get; }

        public AppearanceViewModel Appearance { get; }

        public ReactiveCommand GenerationCommand { get; }

        public CylinderGenerationViewModel()
        {
            this.Cylinder = new Cylinder3dViewModel();
            this.UNum = new ReactiveProperty<int>(36);
            this.VNum = new ReactiveProperty<int>(36);
            this.Appearance = new AppearanceViewModel();
            this.GenerationCommand = new ReactiveCommand();
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new WireFrameBuilder();
            var cylinder = Cylinder.Value;
            builder.Build(cylinder, 25, 25);
            var wireFrame = builder.WireFrame;
            MainModel.Instance.Repository.AddWireFrameScene(wireFrame.Edges, "WFCylinder", Appearance.Value);
            Canvas3d.Instance.Update(MainModel.Instance.Repository);
            Canvas3d.Instance.Render();
        }
    }
}
