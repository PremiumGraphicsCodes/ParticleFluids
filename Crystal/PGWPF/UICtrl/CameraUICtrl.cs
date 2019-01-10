using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PG.Core.Math;

namespace PG.CGStudio.UICtrl
{
    public class CameraUICtrl : IUICtrl
    {
        private PG.CLI.Camera camera;
        private Vector2d prevPosition;

        public CameraUICtrl(PG.CLI.Camera camera)
        {
            this.camera = camera;
            this.prevPosition = new Vector2d();
        }

        public override void OnLeftButtonDown(Vector2d position)
        {
            prevPosition = position;
        }

        public override void OnLeftButtonUp(Vector2d position)
        {
            //Canvas3dView.Instance.Adapter.camera.Move()
        }

        public override void OnLeftButtonDragging(Vector2d position)
        {
            var diff = position - prevPosition;
            camera.Move(new Vector3d(diff.X, diff.Y, 0.0));
            Canvas3dView.Instance.Render();
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
            Canvas3dView.Instance.Render();
            prevPosition = position;
        }

        public override void OnRightButtonUp(Vector2d position)
        {

        }
    }
}
