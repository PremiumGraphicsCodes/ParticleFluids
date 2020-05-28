﻿using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Shape;
using PG.Scene;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.PolygonMesh
{
    public class BoxGenerationViewModel
    {
        public Box3dViewModel BoxViewModel { get; }
            = new Box3dViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        private readonly SceneListModel world;

        private readonly Canvas3d canvas;

        public BoxGenerationViewModel(SceneListModel world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new PolygonMeshBuilder();
            var box = BoxViewModel.Value;
            builder.Add(box);

            var newId = world.AddPolygonMeshScene(builder.ToPolygonMesh(), "PMBox", 1);
            canvas.Camera.Fit();
            canvas.BuildShader(world, newId);
            canvas.Render();
        }
    }
}
