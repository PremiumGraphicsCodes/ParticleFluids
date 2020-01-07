using PG.Control.Math;
using PG.Core.Math;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Shape.Transform
{
    public class ScaleModel
    {
        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public Vector3dViewModel Center { get; }
            = new Vector3dViewModel();

        public Vector3dViewModel Scale { get; }
            = new Vector3dViewModel(new Vector3d(1,1,1));

        public Matrix4d ToMatrix()
        {
            var center = Center.Value;
            var scale = Scale.Value;

            var m1 = new Matrix4d
                (
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                -center.X, -center.Y, -center.Z, 1.0
                );

            var m2 = new Matrix4d
                (
                scale.X, 0.0, 0.0, 0.0,
                0.0, scale.Y, 0.0, 0.0,
                0.0, 0.0, scale.Z, 0.0,
                0.0, 0.0, 0.0, 1.0
                );

            var m3 = new Matrix4d
                (
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                center.X, center.Y, center.Z, 1.0
                );

            return m1 * m2 * m3;
        }
    }
}
