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
            var model = MainModel.Instance.World.Adapter;
            prevPosition = position;
        }

        public override void OnLeftButtonDragging(Vector2d position)
        {
            var model = MainModel.Instance.World.Adapter;
            var gcommand = new PG.CLI.Command(PG.CameraGetLabels.CommandNameLabel);
            gcommand.Execute(MainModel.Instance.World.Adapter);
            var matrix = gcommand.GetResult<Matrix4d>(PG.CameraGetLabels.RotationMatrixLabel);

            var diff = position - prevPosition;
            var bb = PG.CLI.Command.Get<Box3d>(model, PG.GetLabels.BoundingBoxLabel);
            var scale = bb.Min.Distance(bb.Max) * 0.1;
            var v = new Vector4d(diff.X, diff.Y, 0.0, 0.0) * matrix.Transposed();
            var command = new PG.CLI.Command(PG.CameraLabels.CameraTranslateCommandLabel);
            command.SetArg(PG.CameraLabels.TranslateLabel, new Vector3d(v.X, v.Y, v.Z));
            command.Execute(model);
            Canvas3d.Instance.Render();
            prevPosition = position;
        }

        public override void OnRightButtonDown(Vector2d position)
        {
            this.prevPosition = position;
        }

        public override void OnRightButtonDragging(Vector2d position)
        {
            var model = MainModel.Instance.World.Adapter;
            var gcommand = new PG.CLI.Command(PG.CameraGetLabels.CommandNameLabel);
            gcommand.Execute(MainModel.Instance.World.Adapter);
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
            var model = MainModel.Instance.World.Adapter;
            var command = new PG.CLI.Command(PG.CameraLabels.CameraZoomCommandLabel);
            command.SetArg(PG.CameraLabels.ZoomRatioLabel, (float)dx);
            command.Execute(model);
            Canvas3d.Instance.Render();
        }
    }
}
