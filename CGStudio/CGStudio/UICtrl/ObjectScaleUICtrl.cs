using PG.Core.Math;
using Prism.Regions;
using System.Collections.Generic;
using System.Windows;

namespace PG.CGStudio.UICtrl
{
    public class ObjectScaleUICtrl : IUICtrl
    {
        private Vector2d prevPos;

        private readonly List<ObjectModel> Objects;

        public ObjectScaleUICtrl()
        {
            Objects = new List<ObjectModel>();
        }

        public ObjectScaleUICtrl(List<ObjectModel> objects)
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
            var m1 = new Matrix4d
                (
                1.0 + v.X, 0.0, 0.0, 0.0,
                0.0,  1.0 + v.Y, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0
                );
            /*
            var m2 = camera.ProjectionMatrix;

            var matrix = m1 * m2;
            */

            foreach (var o in Objects)
            {
                o.Transform(m1);
            }
            canvas.Update(MainModel.Instance.Repository);
            canvas.Render();

            this.prevPos = position;
        }
    }
}