using PG.Core.Math;
using System.Collections.Generic;

namespace PG.CGStudio.UICtrl
{
    public class TranslateUICtrl : IUICtrl
    {
        private Vector2d prevPos;

        private List<int> ObjectIds;

        public TranslateUICtrl()
        {
            ObjectIds = new List<int>();
        }

        public TranslateUICtrl(List<int> objects)
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
            var command = new PG.CLI.Command("Translate");
            command.SetArg("Translate", v.X, v.Y, 0.0);
            command.Execute(MainModel.Instance.Repository.Adapter);

            canvas.Update(MainModel.Instance.Repository);
        }

    }
}
