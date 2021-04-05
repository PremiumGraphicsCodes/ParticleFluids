using FluidStudio.Space;
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
            = new ReactiveProperty<int>(10);

        public ReactiveProperty<int> ResolutionZ { get; }
            = new ReactiveProperty<int>(10);

        public Sphere3dViewModel SphereViewModel { get; }
            = new Sphere3dViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public SphereGenerationViewModel(MainModel model, SceneList world, Canvas3d canvas)
        {
            this.SphereViewModel.Value = new Sphere3d(10.0, new Vector3d(0, 0, 0));
            this.GenerationCommand.Subscribe(() => OnGenerate(model.SpaceModel, world, canvas));
        }

        private void OnGenerate(SpaceModel space, SceneList world, Canvas3d canvas)
        {
            var res = new int[3];
            res[0] = ResolutionX.Value;
            res[1] = ResolutionY.Value;
            res[2] = ResolutionZ.Value;
            var box = SphereViewModel.Value.GetBoundingBox();
            var newId = space.CreateSparseVolume("SparseVolume", res, box, 1);
            canvas.Camera.Fit();
            canvas.BuildShader(world, newId);
            canvas.Render();

            /*
            var positions = new List<Vector3d>();
            var box = sphere.GetBoundingBox();
            var dx = Dx.Value;
            var dy = Dy.Value;
            var dz = Dz.Value;
            var min = box.Min;
            var max = box.Max;
                        */

            var sphere = SphereViewModel.Value;
            var radius = sphere.Radius;

            var dx = 1.0 / (double)(ResolutionX.Value);
            var dy = 1.0 / (double)(ResolutionY.Value);
            var dz = 1.0 / (double)(ResolutionZ.Value);
            for (var x = -radius; x < radius; x += dx)
            {
                for (var y = -radius; y < radius; y += dy)
                {
                    for (var z = -radius; z < radius; z += dz)
                    {
                        var p = new Vector3d(x, y, z);
                        if (p.LengthSquared < radius * radius)
                        {
                            //positions.Add(p + sphere.Center);
                        }
                    }
                }
            }
            /*
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
