using PG.Core.Math;
using System.Collections.Generic;

namespace PG.CGStudio.UICtrl
{
    public class TranslateUICtrl : IUICtrl
    {
        private Vector2d prevPos;

        private int ObjectId;

        public TranslateUICtrl()
        {
            ObjectId = -1;
        }

        public TranslateUICtrl(int objectId)
        {
            ObjectId = objectId;
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
            command.SetArg("Id", ObjectId);
            command.SetArg("Vector", new Vector3d( v.X, v.Y, 0.0) );
            command.Execute(MainModel.Instance.World.Adapter);

            canvas.Update(MainModel.Instance.World);
            canvas.Render();
        }

    }
}
