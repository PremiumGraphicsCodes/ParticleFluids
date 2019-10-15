using PG.Core.Math;

namespace PG.CGStudio.UICtrl
{
    public class RotateUICtrl : IUICtrl
    {
        private Vector2d prevPos;

        private int ObjectId;

        public RotateUICtrl()
        {
            ObjectId = -1;
        }

        public RotateUICtrl(int objectId)
        {
            this.ObjectId = objectId;
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

            var v = (position - prevPos) * 0.1;
            var command = new PG.CLI.Command("Scale");
            command.SetArg("Id", ObjectId);
            command.SetArg("Ratio", new Vector3d(v.X + 1.0, v.Y + 1.0, 1.0));
            command.Execute(MainModel.Instance.Repository.Adapter);

            canvas.Update(MainModel.Instance.Repository);
            canvas.Render();
            */
        }

    }
}
