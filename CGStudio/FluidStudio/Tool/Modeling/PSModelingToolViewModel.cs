using PG.Control.Math;
using PG.Core.Math;
using PG.Core.UI;
using PG.Scene;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.Tool.Modeling
{
    public class PSModelingToolViewModel
    {
        public Box3dViewModel BoundingBoxViewModel { get; }
            = new Box3dViewModel();

        public ReactiveProperty<float> Dx = new ReactiveProperty<float>(1.0f);

        public ReactiveProperty<float> Dy = new ReactiveProperty<float>(1.0f);

        public ReactiveProperty<float> Dz = new ReactiveProperty<float>(1.0f);

        public ReactiveCommand GenerateCommand { get; }
            = new ReactiveCommand();

        private readonly SceneList scenes;

        public PSModelingToolViewModel(SceneList scenes)
        {
            this.scenes = scenes;
        }

        private void OnGenerate()
        {
            var positions = new List<Vector3d>();
            var box = BoundingBoxViewModel.Value;
            var length = box.Length;
            var dx = Dx.Value;
            var dy = Dy.Value;
            var dz = Dz.Value;
            var min = box.Min;
            var max = box.Max;
            for (var x = min.X; x < max.X; x += dx)
            {
                for (var y = min.Y; y < max.Y; y += dy)
                {
                    for (var z = min.Z; z < max.Z; z += dz)
                    {
                        var p = new Vector3d(x, y, z);
                        positions.Add(p);
                    }
                }
            }
            var appearance = new ParticleAppearance();
            appearance.Color = new PG.Core.Graphics.ColorRGBA(1, 1, 1, 1);
            appearance.Size = 10.0f;
            var newId = scenes.AddParticleSystemScene(positions, "PSBox", appearance, 1);
            /*
            canvas.Camera.Fit();
            canvas.BuildShader(world, newId);
            canvas.Render();
            */

        }
    }
}
