using PG.Core.Math;

namespace PG.CGStudio.UICtrl
{
    public class ScaleUICtrl : IUICtrl
    {
        private Vector2d prevPos = new Vector2d(0,0);

        private Vector3d scale = new Vector3d(1,1,1);

        public int ShapeId { get; set; }

        public Vector3d Center { get; set; }
            = new Vector3d(0, 0, 0);

        public double Sensitivity { get; set; } = 1.0;

        public ScaleUICtrl()
        {
        }

        public override void OnLeftButtonDown(Vector2d position)
        {
            this.prevPos = position;
        }

        public override void OnLeftButtonUp(Vector2d position)
        {

        }

        public override void OnLeftButtonDragging(Vector2d position)
        {
            var model = MainModel.Instance;
            var diff = (position - prevPos) * Sensitivity;
            var matrix = PG.CLI.Command.Get<Matrix4d>(model.World.Adapter, PG.GetLabels.CameraRotationMatrixLabel);
            var v = matrix * new Vector4d(diff.X, diff.Y, 0.0, 1.0);
            scale += new Vector3d(v.X, v.Y, v.Z);

            MainModel.Instance.World.Scenes.SetMatrix(ShapeId, ToMatrix());

            var canvas = Canvas3d.Instance;
            canvas.Update(MainModel.Instance.World);
            canvas.Render();

            this.prevPos = position;
        }

        public Matrix4d ToMatrix()
        {
            var m1 = new Matrix4d
                (
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                -Center.X, -Center.Y, -Center.Z, 1.0
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
                Center.X, Center.Y, Center.Z, 1.0
                );

            return m1 * m2 * m3;
        }
    }
}
