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
            var v = (position - prevPos) * 0.1;
            vectorViewModel.Value += new Vector3d(v.X, v.Y, 0.0);
        }
    }
}
