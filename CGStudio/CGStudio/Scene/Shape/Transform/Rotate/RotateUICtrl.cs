
using PG.CGStudio.Scene.Shape.Transform;
using PG.Control.Math;
using PG.Core.Math;

namespace PG.CGStudio.UICtrl
{
    public class RotateUICtrl : IUICtrl
    {
        private Vector2d prevPos;

        private readonly RotateViewModel model;

        public RotateUICtrl()
        {
        }

        public RotateUICtrl(RotateViewModel model)
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
            var diff = (position - prevPos) * 10.0;
            var matrix = World.Instance.Camera.GetRotationMatrix();
            var v = matrix * new Vector4d(diff.Y, diff.X, 0.0, 1.0);
            model.AngleViewModel.Value += new Vector3d(v.X, v.Y, v.Z);
            model.SetMatrix(true);

            this.prevPos = position;

        }

    }
}
