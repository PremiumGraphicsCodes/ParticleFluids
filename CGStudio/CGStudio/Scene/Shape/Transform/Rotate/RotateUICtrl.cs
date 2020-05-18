
using PG.CGStudio.Scene.Shape.Transform;
using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Math;
using System.Windows.Input;

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

        public void OnLeftButtonDown(Vector2d position)
        {
            this.prevPos = position;
        }

        public void OnLeftButtonUp(Vector2d position)
        {

        }

        public void OnLeftButtonDragging(Vector2d position)
        {
            var diff = (position - prevPos) * 10.0;
            var matrix = Canvas3d.Instance.Camera.GetRotationMatrix();
            var v = matrix * new Vector4d(diff.Y, diff.X, 0.0, 1.0);
            model.AngleViewModel.Value += new Vector3d(v.X, v.Y, v.Z);
            model.SetMatrix(true);

            this.prevPos = position;

        }

        public void OnRightButtonDown(Vector2d position)
        {
            ;
        }

        public void OnRightButtonDragging(Vector2d position)
        {
            ;
        }

        public void OnRightButtonUp(Vector2d position)
        {
            ;
        }

        public void OnMiddleButtonDown(Vector2d position)
        {
            ;
        }

        public void OnMiddleButtonDragging(Vector2d position)
        {
            ;
        }

        public void OnMiddleButtonUp(Vector2d position)
        {
            ;
        }

        public void OnWheel(double dx)
        {
            ;
        }

        public void OnKeyDown(Key key)
        {
            ;
        }

        public void OnKeyUp(Key key)
        {
            ;
        }
    }
}
