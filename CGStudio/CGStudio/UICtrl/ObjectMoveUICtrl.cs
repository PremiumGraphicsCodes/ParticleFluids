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
            var v = position - prevPos;
            foreach(var o in Objects)
            {
                o.Move(new Vector3d(v.X, v.Y, 0.0));
            }
            this.prevPos = position;
            Canvas3d.Instance.Update(MainModel.Instance.Repository);
            Canvas3d.Instance.Render();
        }

    }
}
