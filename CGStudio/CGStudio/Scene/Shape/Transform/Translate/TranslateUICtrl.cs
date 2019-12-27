using PG.Control.Math;
using PG.Core.Math;
using System.Collections.Generic;

namespace PG.CGStudio.UICtrl
{
    public class TranslateUICtrl : IUICtrl
    {
        private Vector2d prevPos;

        private double sensivitiy = 0.1;

        private Vector3dViewModel vectorViewModel;

        public double Sensivity { set { this.sensivitiy = value; } }

        public TranslateUICtrl()
        {
        }

        public TranslateUICtrl(Vector3dViewModel vectorViewModel)
        {
            this.vectorViewModel = vectorViewModel;
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
            var v = matrix * new Vector4d(diff.X, diff.Y, 0.0, 0.0);
            vectorViewModel.Value += new Vector3d(v.X, v.Y, v.Z);

            this.prevPos = position;
        }

    }
}
