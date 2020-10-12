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
    public class BoxGenerationViewModel : BindableBase
    {
        public ReactiveProperty<int> Count { get; }
            = new ReactiveProperty<int>(10000);

        public Box3dViewModel BoxViewModel { get; }
            = new Box3dViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<double> Dx { get; }
            = new ReactiveProperty<double>(0.1);

        public ReactiveProperty<double> Dy { get; }
            = new ReactiveProperty<double>(0.1);

        public ReactiveProperty<double> Dz { get; }
            = new ReactiveProperty<double>(0.1);

        public BoxGenerationViewModel(SceneList world, Canvas3d canvas)
        {
            this.GenerationCommand.Subscribe(() => OnGenerate(world, canvas));
        }

        private void OnGenerate(SceneList world, Canvas3d canvas)
        {
            var positions = new List<Vector3d>();
            var box = BoxViewModel.Value;
            var length = box.Length;
            var dx = Dx.Value;
            var dy = Dy.Value;
            var dz = Dz.Value;
            var min = box.Min;
            var max = box.Max;
            for(var x = min.X; x < max.X; x+= dx)
            {
                for(var y = min.Y; y < max.Y; y+=dy)
                {
                    for(var z = min.Z; z < max.Z; z+=dz)
                    {
                        var p = new Vector3d(x, y, z);
                        positions.Add(p);
                    }
                }
            }
            var appearance = new ParticleAppearance();
            appearance.Color = new PG.Core.Graphics.ColorRGBA(1, 1, 1, 1);
            appearance.Size = 10.0f;
            var newId = world.AddParticleSystemScene(positions, "PSBox", appearance, 1);
            canvas.Camera.Fit();
            canvas.BuildShader(world, newId);
            canvas.Render();
        }
    }
}
