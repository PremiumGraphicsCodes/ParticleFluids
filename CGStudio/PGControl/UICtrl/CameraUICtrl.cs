using System.Windows.Input;
using PG.Core.Math;

namespace PG.CGStudio.UICtrl
{
    public class CameraUICtrl : IUICtrl
    {
        private Vector2d prevPosition;

        public CameraUICtrl()
        {
            this.prevPosition = new Vector2d();
        }

        public override void OnLeftButtonDown(Vector2d position)
        {
            prevPosition = position;
        }

        public override void OnLeftButtonDragging(Vector2d position)
        {
            var model = World.Instance.Adapter;
            var matrix = World.Instance.Camera.GetRotationMatrix();

            var diff = position - prevPosition;
            var bb = World.Instance.Scenes.GetBoundingBox(0);
            var scale = bb.Min.Distance(bb.Max) * 0.1;
            var v = new Vector4d(diff.X, diff.Y, 0.0, 0.0) * matrix.Transposed();
            World.Instance.Camera.Translate(new Vector3d(v.X, v.Y, v.Z));
            Canvas3d.Instance.Render();
            prevPosition = position;
        }

        public override void OnRightButtonDown(Vector2d position)
        {
            this.prevPosition = position;
        }

        public override void OnRightButtonDragging(Vector2d position)
        {
            var model = World.Instance.Adapter;
            var gcommand = new PG.CLI.Command(PG.CameraGetLabels.CommandNameLabel);
            gcommand.Execute(World.Instance.Adapter);
            var matrix = gcommand.GetResult<Matrix4d>(PG.CameraGetLabels.RotationMatrixLabel);

            var diff = position - prevPosition;
            var v = new Vector4d(diff.Y, diff.X, 0.0, 0.0) * matrix.Transposed();
            var command = new PG.CLI.Command(PG.CameraLabels.CameraRotateCommandLabel);
            var matrix1 = Matrix3d.RotationX(v.X);
            var matrix2 = Matrix3d.RotationY(v.Y);
            var matrix3 = Matrix3d.RotationZ(v.Z);
            command.SetArg(PG.CameraLabels.MatrixLabel, matrix3 * matrix2 * matrix1);
            command.Execute(model);
            Canvas3d.Instance.Render();
            prevPosition = position;
        }

        public override void OnWheel(double dx)
        {
            var model = World.Instance.Adapter;
            var command = new PG.CLI.Command(PG.CameraLabels.CameraZoomCommandLabel);
            command.SetArg(PG.CameraLabels.ZoomRatioLabel, (float)dx);
            command.Execute(model);
            Canvas3d.Instance.Render();
        }
    }
}
