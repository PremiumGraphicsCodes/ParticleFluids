using PG.CGStudio.Scene.Shape.Transform;
using PG.CGStudio.Scene.Shape.Transform.Scale;
using PG.Core.Math;
using System.Windows.Input;

namespace PG.CGStudio.UICtrl
{
    public class ScaleUICtrl : IUICtrl
    {
        private Vector2d prevPos = new Vector2d(0,0);

        private readonly ScaleViewModel model;

        public double Sensitivity { get; set; } = 1.0;

        public ScaleUICtrl(ScaleViewModel model)
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
            var diff = (position - prevPos) * Sensitivity;
            var matrix = World.Instance.Camera.GetRotationMatrix();
            var v = matrix * new Vector4d(diff.X, diff.Y, 0.0, 1.0);
            model.RatioViewModel.Value += new Vector3d(v.X, v.Y, v.Z);
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
