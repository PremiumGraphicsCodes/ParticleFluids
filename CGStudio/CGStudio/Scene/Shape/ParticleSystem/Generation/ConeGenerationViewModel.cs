using PG.CGStudio.Generation.ParticleSystem;
using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Math;
using PG.Scene;
using Reactive.Bindings;
using System.Collections.Generic;

namespace PG.CGStudio.Scene.Shape.ParticleSystem.Generation
{
    public class ConeGenerationViewModel
    {
        public Cone3dViewModel ConeViewModel { get; }
            = new Cone3dViewModel();

        public ReactiveProperty<int> Count { get; }
            = new ReactiveProperty<int>(10000);

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public AppearanceViewModel AppearanceViewModel { get; }
            = new AppearanceViewModel();

        private readonly SceneList scene;

        private readonly Canvas3d canvas;

        public ConeGenerationViewModel(SceneList world, Canvas3d canvas)
        {
            this.scene = world;
            this.canvas = canvas;
            GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var random = new System.Random();
            var positions = new List<Vector3d>();
            var torus = ConeViewModel.Value;
            for (int i = 0; i < Count.Value; ++i)
            {
                var u = random.NextDouble();
                var v = random.NextDouble();
                var w = random.NextDouble();
                var pos = torus.GetPosition(u, v, w);
                positions.Add(pos);
            }
            var id = scene.AddParticleSystemScene(positions, "PSCone", AppearanceViewModel.Value, 1);
            canvas.Camera.Fit();
            canvas.BuildShader(scene, id);
            canvas.Render();
        }
    }
}
