using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Math;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;

namespace FluidStudio.Scene.SparseVolume
{
    class SphereGenerationViewModel : BindableBase
    {
        public ReactiveProperty<int> ResolutionX { get; }
            = new ReactiveProperty<int>(10);

        public ReactiveProperty<int> ResolutionY { get; }
            = new ReactiveProperty<int>();

        public ReactiveProperty<int> ResolutionZ { get; }
            = new ReactiveProperty<int>();

        public Sphere3dViewModel SphereViewModel { get; }
            = new Sphere3dViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public SphereGenerationViewModel(SceneList world, Canvas3d canvas)
        {
            this.SphereViewModel.Value = new Sphere3d(10.0, new Vector3d(0, 0, 0));
            this.GenerationCommand.Subscribe(() => OnGenerate(world, canvas));
        }

        private void OnGenerate(SceneList world, Canvas3d canvas)
        {
            /*
            var positions = new List<Vector3d>();
            var sphere = SphereViewModel.Value;
            var box = sphere.GetBoundingBox();
            var dx = Dx.Value;
            var dy = Dy.Value;
            var dz = Dz.Value;
            var min = box.Min;
            var max = box.Max;
            var radius = sphere.Radius;
            for (var x = -radius; x < radius; x += dx)
            {
                for (var y = -radius; y < radius; y += dy)
                {
                    for (var z = -radius; z < radius; z += dz)
                    {
                        var p = new Vector3d(x, y, z);
                        if (p.LengthSquared < radius * radius)
                        {
                            positions.Add(p + sphere.Center);
                        }
                    }
                }
            }
            var appearance = new ParticleAppearance();
            appearance.Color = new PG.Core.Graphics.ColorRGBA(1, 1, 1, 1);
            appearance.Size = 10.0f;
            var newId = world.AddParticleSystemScene(positions, "PSSphere", appearance, 1);
            canvas.Camera.Fit();
            canvas.BuildShader(world, newId);
            canvas.Render();
            */
        }
    }
}
