using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Math;
using PG.Core.UI;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;
using System.Collections.Generic;

namespace FluidStudio.Scene.ParticleSystem
{
    public class QuadGenerationViewModel : BindableBase
    {
        public Quad3dViewModel QuadViewModel { get; }
            = new Quad3dViewModel();

        public ReactiveProperty<double> Du { get; }
            = new ReactiveProperty<double>(0.1);

        public ReactiveProperty<double> Dv { get; }
            = new ReactiveProperty<double>(0.1);

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public QuadGenerationViewModel(SceneList world, Canvas3d canvas)
        {
            this.GenerationCommand.Subscribe(() => OnGenerate(world, canvas));
        }
        private void OnGenerate(SceneList world, Canvas3d canvas)
        {
            var quad = QuadViewModel.Value;
            var du = Du.Value;
            var dv = Dv.Value;
            var unum = quad.UVec.Length / du;
            var vnum = quad.VVec.Length / dv;

            var positions = new List<Vector3d>();
            for (int u = 0; u < unum; ++u)
            {
                for (int v = 0; v < vnum; ++v)
                {
                    var uu = u / (double)unum;
                    var vv = v / (double)vnum;
                    var p = quad.GetPosition(uu, vv);
                    positions.Add(p);
                }
            }
            var appearance = new ParticleAppearance();
            appearance.Color = new PG.Core.Graphics.ColorRGBA(1, 1, 1, 1);
            appearance.Size = 10.0f;
            var newId = world.AddParticleSystemScene(positions, "PSQuad", appearance, 1);
            canvas.Camera.Fit();
            canvas.BuildShader(world, newId);
            canvas.Render();

        }
    }
}