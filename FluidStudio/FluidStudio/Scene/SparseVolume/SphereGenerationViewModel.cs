using FluidStudio.Space;
using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Math;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;
using System.Collections.Generic;

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

            var sphere = SphereViewModel.Value;
            var radius = sphere.Radius;

            var nodes = new List<SparseVolumeNode>();

            var resx = ResolutionX.Value;
            var resy = ResolutionY.Value;
            var resz = ResolutionZ.Value;
            for (var x = 0; x < resx; x ++)
            {
                for (var y = 0; y < resy; y++)
                {
                    for (var z = 0; z < resz; z++)
                    {
                        var index = new int[3];
                        index[0] = x;
                        index[1] = y;
                        index[2] = z;
                        var pos = getPositionAt(index, box);
                        var distanceSquared = pos.DistanceSquared(sphere.Center);
                        if (distanceSquared < radius * radius)
                        {
                            var distance = System.Math.Sqrt(distanceSquared);
                            var value = distance / radius;
                            var node = new SparseVolumeNode(index, (float)value);
                        }
                    }
                }
            }
        }

        private Vector3d getPositionAt(int[] index, Box3d bb)
        {
            var u = index[0] / (double)(ResolutionX.Value);
            var v = index[1] / (double)(ResolutionY.Value);
            var w = index[2] / (double)(ResolutionZ.Value);

            return bb.GetPosition(u, v, w);
        }
    }
}
