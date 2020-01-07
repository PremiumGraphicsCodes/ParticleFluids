using PG.Control.Math;
using PG.Core.Math;
using System.Collections.Generic;

namespace PG.CGStudio.UICtrl
{
    public class TranslateUICtrl : IUICtrl
    {
        private Vector2d prevPos;

        private double sensivitiy = 0.1;

        private readonly int id;

        private Vector3d translate = new Vector3d(0,0,0);

        public double Sensivity { set { this.sensivitiy = value; } }

        public TranslateUICtrl(int id)
        {
            this.id = id;
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
            var diff = (position - prevPos) * sensivitiy;
            var matrix = PG.CLI.Command.Get<Matrix4d>(model.World.Adapter, PG.GetLabels.CameraRotationMatrixLabel);
            var v = matrix * new Vector4d(-diff.X, diff.Y, 0.0, 0.0);
            translate += new Vector3d(v.X, v.Y, v.Z);
            MainModel.Instance.World.Scenes.SetMatrix(id, ToMatrix());

            var canvas = Canvas3d.Instance;
            canvas.Update(MainModel.Instance.World);
            canvas.Render();

            this.prevPos = position;
        }

        public Matrix4d ToMatrix()
        {
            return new Matrix4d
                (
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                translate.X, translate.Y, translate.Z, 1.0
                );
        }

    }
}
