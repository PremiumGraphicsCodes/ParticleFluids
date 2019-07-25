using PG.Core.Math;
using Prism.Regions;
using System.Collections.Generic;
using System.Windows;

namespace PG.CGStudio.UICtrl
{
    public class ObjectScaleUICtrl : IUICtrl
    {
        private Vector2d prevPos;

        private readonly List<int> ObjectIds;

        public ObjectScaleUICtrl()
        {
            ObjectIds = new List<int>();
        }

        public ObjectScaleUICtrl(List<int> objects)
        {
            ObjectIds = objects;
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
            /*
            var canvas = Canvas3d.Instance;
            var camera = canvas.Camera;

            var v = (position - prevPos) * 0.1;
            var m1 = new Matrix4d
                (
                1.0 + v.X, 0.0, 0.0, 0.0,
                0.0,  1.0 + v.Y, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0
                );

            foreach (var id in ObjectIds)
            {
                var o = MainModel.Instance.Repository.Objects.FindObjectById(id);
                if (o != null)
                {
                    o.Transform(m1);
                }
            }
            canvas.Update(MainModel.Instance.Repository);
            canvas.Render();

            this.prevPos = position;
            */
        }
    }
}