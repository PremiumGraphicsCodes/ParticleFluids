using PG.Control.Math;
using PG.Core.Math;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.CGStudio.Scene.Shape.Transform
{
    public class RotateModel
    {
        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public Vector3dViewModel AngleViewModel { get; }
            = new Vector3dViewModel();

        public Matrix4d ToMatrix()
        {
            var rx = AngleViewModel.X.Value / 180.0 * System.Math.PI;
            var ry = AngleViewModel.Y.Value / 180.0 * System.Math.PI;
            var rz = AngleViewModel.Z.Value / 180.0 * System.Math.PI;

            var matrix = Matrix3d.RotationZ(rz) * Matrix3d.RotationY(ry) * Matrix3d.RotationX(rx);
            return new Matrix4d(matrix);
        }

    }
}
