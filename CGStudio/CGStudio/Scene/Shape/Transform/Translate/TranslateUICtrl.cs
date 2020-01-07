using PG.CGStudio.Scene.Shape.Transform;
using PG.Control.Math;
using PG.Core.Math;
using System.Collections.Generic;

namespace PG.CGStudio.UICtrl
{
    public class TranslateUICtrl : IUICtrl
    {
        private Vector2d prevPos;

        private double sensivitiy = 0.1;

        private readonly TranslateModel model;

        public double Sensivity { set { this.sensivitiy = value; } }

        public TranslateUICtrl(TranslateModel model)
        {
            this.model = model;
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
            var mainModel = MainModel.Instance;
            var diff = (position - prevPos) * sensivitiy;
            var matrix = PG.CLI.Command.Get<Matrix4d>(mainModel.World.Adapter, PG.GetLabels.CameraRotationMatrixLabel);
            var v = matrix * new Vector4d(-diff.X, diff.Y, 0.0, 0.0);
            model.Translate.Value += new Vector3d(v.X, v.Y, v.Z);
            MainModel.Instance.World.Scenes.SetMatrix(model.Id.Value, model.ToMatrix());

            var canvas = Canvas3d.Instance;
            canvas.Update(MainModel.Instance.World);
            canvas.Render();

            this.prevPos = position;
        }


    }
}
