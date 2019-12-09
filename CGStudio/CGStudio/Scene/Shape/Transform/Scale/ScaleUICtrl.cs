using PG.Control.Math;
using PG.Core.Math;

namespace PG.CGStudio.UICtrl
{
    public class ScaleUICtrl : IUICtrl
    {
        private Vector2d prevPos;

        private Vector3dViewModel vectorViewModel;

        public ScaleUICtrl()
        {
        }

        public ScaleUICtrl(Vector3dViewModel vectorViewModel)
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
            var diff = (position - prevPos) * 0.1;
            var matrix = PG.CLI.Command.Get<Matrix4d>(model.World.Adapter, PG.GetLabels.CameraRotationMatrixLabel);
            var v = new Vector4d(diff.X, diff.Y, 0.0, 0.0) * matrix;
            vectorViewModel.Value += new Vector3d(v.X, v.Y, v.Z);
        }
    }
}
