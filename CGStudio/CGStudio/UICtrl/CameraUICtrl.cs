using PG.Core.Math;

namespace PG.CGStudio.UICtrl
{
    public class CameraUICtrl : IUICtrl
    {
        private PG.CLI.CameraAdapter camera;
        private Vector2d prevPosition;

        public CameraUICtrl(PG.CLI.CameraAdapter camera)
        {
            this.camera = camera;
            this.prevPosition = new Vector2d();
        }

        public override void OnLeftButtonDown(Vector2d position)
        {
            prevPosition = position;
        }

        public override void OnLeftButtonDragging(Vector2d position)
        {
            var diff = position - prevPosition;
            camera.Move(new Vector3d(diff.X, diff.Y, 0.0));
            OpenGLPresenter.Instance.Render();
            prevPosition = position;
        }

        public override void OnRightButtonDown(Vector2d position)
        {
            this.prevPosition = position;
        }

        public override void OnRightButtonDragging(Vector2d position)
        {
            var diff = position - prevPosition;
            camera.Rotate(diff.X, diff.Y);
            OpenGLPresenter.Instance.Render();
            prevPosition = position;
        }

        public override void OnWheel(double dx)
        {
            camera.Zoom(dx);
            OpenGLPresenter.Instance.Render();
        }
    }
}
