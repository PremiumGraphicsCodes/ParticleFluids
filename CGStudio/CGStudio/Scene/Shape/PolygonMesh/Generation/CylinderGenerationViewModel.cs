﻿using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Shape;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.PolygonMesh
{
    public class CylinderGenerationViewModel : BindableBase
    {
        public Cylinder3dViewModel CylinderViewModel { get; }

        public ReactiveCommand GenerateCommand { get; }

        public ReactiveProperty<int> UNum { get; }

        public ReactiveProperty<int> VNum { get; }

        public CylinderGenerationViewModel()
        {
            CylinderViewModel = new Cylinder3dViewModel();
            GenerateCommand = new ReactiveCommand();
            GenerateCommand.Subscribe(OnGenerate);
            UNum = new ReactiveProperty<int>(24);
            VNum = new ReactiveProperty<int>(24);
        }

        private void OnGenerate()
        {
            var builder = new PolygonMeshBuilder();
            builder.Add(CylinderViewModel.Value, UNum.Value);

            World.Instance.Scenes.AddPolygonMeshScene(builder.ToPolygonMesh(), "PMCylinder", 1);
            World.Instance.Scenes.Sync();
            Canvas3d.Instance.Camera.Fit();

            Canvas3d.Instance.Update(World.Instance);
            Canvas3d.Instance.Render();
        }
    }
}
