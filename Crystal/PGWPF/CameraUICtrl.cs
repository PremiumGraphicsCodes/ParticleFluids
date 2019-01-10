using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PG.Core.Math;

namespace PG.CGStudio
{
    public abstract class UICtrl
    {
        public virtual void OnLeftButtonDown(Vector2d position) { }

        public virtual void OnLeftButtonDragging(Vector2d position) { }

        public virtual void OnLeftButtonUp(Vector2d position) { }

        public virtual void OnRightButtonDown(Vector2d position) { }

        public virtual void OnRightButtonDragging(Vector2d position) { }

        public virtual void OnRightButtonUp(Vector2d position) { }
    }

    public class CameraUICtrl : UICtrl
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
            var diff = position - prevPosition;
            //camera.Move(new Vector3d(position.x)

             //   this.prevPosition = position;
        }

        public override void OnLeftButtonUp(Vector2d position)
        {
            //Canvas3dView.Instance.Adapter.camera.Move()
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
