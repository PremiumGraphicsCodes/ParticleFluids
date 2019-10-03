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
            var canvas = Canvas3d.Instance;

            var v = (position - prevPos) * 0.1;
            var command = new PG.CLI.Command("Scale");
            command.SetArg("Scale", v.X + 1.0, v.Y + 1.0, 1.0);
            command.Execute(MainModel.Instance.Repository.Adapter);

            canvas.Update(MainModel.Instance.Repository);

        }
    }
}