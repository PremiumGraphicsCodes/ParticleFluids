
using PG.Control.Math;
using PG.Core.Math;

namespace PG.CGStudio.UICtrl
{
    public class RotateUICtrl : IUICtrl
    {
        private Vector2d prevPos;

        private Vector3dViewModel rotationViewModel;

        public RotateUICtrl()
        {
        }

        public RotateUICtrl(Vector3dViewModel rotationViewModel)
        {
            this.rotationViewModel = rotationViewModel;
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
            var diff = (position - prevPos) * 10.0;
            var matrix = PG.CLI.Command.Get<Matrix4d>(model.World.Adapter, PG.GetLabels.CameraRotationMatrixLabel);
            var v = matrix * new Vector4d(diff.Y, diff.X, 0.0, 1.0);
            rotationViewModel.Value += new Vector3d(v.X, v.Y, v.Z);

            this.prevPos = position;

        }

    }
}
