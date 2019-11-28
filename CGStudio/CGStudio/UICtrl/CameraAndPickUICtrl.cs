using System.Windows.Input;
using PG.Core.Math;

namespace PG.CGStudio.UICtrl
{
    public class CameraAndPickUICtrl : IUICtrl
    {
        private Vector2d prevPosition;

        public CameraAndPickUICtrl()
        {
            this.prevPosition = new Vector2d();
        }

        public override void OnLeftButtonDown(Vector2d position)
        {
            var model = MainModel.Instance.World.Adapter;

            var objectId = Canvas3d.Instance.GetObjectId(position);

            if (objectId.parentId != 0)
            {
                if (MainModel.Instance.World.Scenes.IsSelected(objectId.parentId))
                {
                    MainModel.Instance.World.Scenes.UnSelect(objectId.parentId);
                }
                else
                {
                    MainModel.Instance.World.Scenes.Select(objectId.parentId);
                }
                return;
            }

            prevPosition = position;
        }

        public override void OnLeftButtonDragging(Vector2d position)
        {
            var model = MainModel.Instance.World.Adapter;
            var diff = position - prevPosition;
            var command = new PG.CLI.Command(PG.CameraLabels.CameraTranslateCommandLabel);
            command.SetArg(PG.CameraLabels.TranslateLabel, new Vector3d(diff.X, diff.Y, 0.0));
            command.Execute(model);
            Canvas3d.Instance.Render();
            prevPosition = position;
        }

        public override void OnRightButtonDown(Vector2d position)
        {
            this.prevPosition = position;
        }

        public override void OnRightButtonDragging(Vector2d position)
        {
            var model = MainModel.Instance.World.Adapter;
            var diff = position - prevPosition;
            var command = new PG.CLI.Command(PG.CameraLabels.CameraRotateCommandLabel);
            command.SetArg(PG.CameraLabels.RxLabel, (float)diff.X);
            command.SetArg(PG.CameraLabels.RyLabel, (float)diff.Y);
            command.Execute(model);
            Canvas3d.Instance.Render();
            prevPosition = position;
        }

        public override void OnWheel(double dx)
        {
            var model = MainModel.Instance.World.Adapter;
            var command = new PG.CLI.Command(PG.CameraLabels.CameraZoomCommandLabel);
            command.SetArg(PG.CameraLabels.ZoomRatioLabel, (float)dx);
            command.Execute(model);
            Canvas3d.Instance.Render();
        }

        public override void OnKeyDown(Key key)
        {
            if (key == Key.Delete)
            {
                var model = MainModel.Instance.World;
                var selecteds = model.Scenes.SelectedIds;
                foreach (var id in selecteds)
                {
                    model.Scenes.UnSelect(id);
                    model.Scenes.Delete(id);
                }
            }
        }
    }
}
