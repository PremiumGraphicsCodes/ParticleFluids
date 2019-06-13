using PG.Core.Math;
using System.Collections.Generic;

namespace PG.CGStudio.UICtrl
{
    public class ObjectMoveUICtrl : IUICtrl
    {
        private Vector2d prevPos;

        private List<ObjectModel> Objects;

        public ObjectMoveUICtrl()
        {
            Objects = new List<ObjectModel>();
        }

        public ObjectMoveUICtrl(List<ObjectModel> objects)
        {
            Objects = objects;
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
            var canvas = Canvas3d.Instance;
            var camera = canvas.Camera;

            var v = (position - prevPos) * 0.1;
                        /*
            var m1 = new Matrix4d
                (
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                v.X, v.Y, 0.0, 1.0
                );
            var m2 = camera.ProjectionMatrix;

            var matrix = m2 * m1;
            */

            foreach(var o in Objects)
            {
                o.Move(new Vector3d(v, 0.0));
            }
            this.prevPos = position;
            Canvas3d.Instance.Update(MainModel.Instance.Repository);
            Canvas3d.Instance.Render();
        }

    }
}
