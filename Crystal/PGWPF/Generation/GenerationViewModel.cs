﻿using PG.App.Generation.PolygonMesh;
using PG.CGStudio.Generation.ParticleSystem;
using PG.CGStudio.Generation.PolygonMesh;
using PG.CGStudio.Generation.WireFrame;
using Reactive.Bindings;

namespace PG.CGStudio.Generation
{
    public class GenerationViewModel
    {
        public ReactiveCommand ParticleSystemGenerationCommand { get; }

        public ReactiveCommand WireFrameGenerationCommand { get; }

        public ReactiveCommand PolygonMeshGenerationCommand { get; }

        public GenerationViewModel()
        {
            this.ParticleSystemGenerationCommand = new ReactiveCommand();
            this.ParticleSystemGenerationCommand.Subscribe(OnParticleSystemGeneration);

            this.WireFrameGenerationCommand = new ReactiveCommand();
            this.WireFrameGenerationCommand.Subscribe(OnWireFrameGeneration);

            this.PolygonMeshGenerationCommand = new ReactiveCommand();
            this.PolygonMeshGenerationCommand.Subscribe(OnPolygonMeshGeneration);
        }

        private void OnParticleSystemGeneration()
        {
            var dialog = new ParticleSystemGenerationView();
            dialog.DataContext = new ParticleSystemGenerationViewModel();
            dialog.Show();
        }

        private void OnWireFrameGeneration()
        {
            var dialog = new WireFrameGenerationView();
            dialog.Show();
        }

        private void OnPolygonMeshGeneration()
        {
            var dialog = new PolygonMeshGenerationView();
            dialog.DataContext = new PolygonMeshGenerationViewModel();
            dialog.Show();
        }
    }
}
