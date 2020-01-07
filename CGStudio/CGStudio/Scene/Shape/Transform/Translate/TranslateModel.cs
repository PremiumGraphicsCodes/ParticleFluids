using PG.Control.Math;
using PG.Core.Math;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Shape.Transform
{
    public class TranslateModel
    {
        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public Vector3dViewModel Translate { get; }
            = new Vector3dViewModel();

        public Matrix4d ToMatrix()
        {
            var t = Translate.Value;
            return new Matrix4d
                (
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                t.X, t.Y, t.Z, 1.0
                );
        }
    }
}
