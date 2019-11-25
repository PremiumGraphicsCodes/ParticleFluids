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

            Canvas3d.Instance.Renderer.Bind();
            var command = new PG.CLI.Command(PG.PickLabels.PickCommandLabel);
            command.SetArg(PG.PickLabels.PositionLabel, new Vector2d(position.X, 1.0 - position.Y));
            command.Execute(model);
            var parentId = command.GetResult<int>(PG.PickLabels.ParentIdLabel);
            var childId = command.GetResult<int>(PG.PickLabels.ChildIdLabel);
            Canvas3d.Instance.Renderer.UnBind();

            if (parentId != 0)
            {
                command.Create(PG.ShapeSelectLabels.CommandNameLabel);
                command.SetArg(PG.ShapeSelectLabels.ShapeIdLabel, parentId);
                command.Execute(model);
                Canvas3d.Instance.Update(MainModel.Instance.World);
                Canvas3d.Instance.Render();
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
    }
}
