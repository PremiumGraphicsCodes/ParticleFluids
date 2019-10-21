﻿using PG.Core.Math;

namespace PG.CGStudio.UICtrl
{
    public class CameraUICtrl : IUICtrl
    {
        private Vector2d prevPosition;

        public CameraUICtrl()
        {
            this.prevPosition = new Vector2d();
        }

        public override void OnLeftButtonDown(Vector2d position)
        {
            prevPosition = position;
        }

        public override void OnLeftButtonDragging(Vector2d position)
        {
            var model = MainModel.Instance.World.Adapter;
            var diff = position - prevPosition;
            var command = new PG.CLI.Command("CameraTranslate");
            command.SetArg("Translate", new Vector3d(diff.X, diff.Y, 0.0));
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
            var command = new PG.CLI.Command("CameraRotate");
            command.SetArg("Rx", (float)diff.X);
            command.SetArg("Ry", (float)diff.Y);
            command.Execute(model);
            Canvas3d.Instance.Render();
            prevPosition = position;
        }

        public override void OnWheel(double dx)
        {
            var model = MainModel.Instance.World.Adapter;
            var command = new PG.CLI.Command("CameraZoom");
            command.SetArg("Ratio", (float)dx);
            command.Execute(model);
            Canvas3d.Instance.Render();
        }
    }
}
