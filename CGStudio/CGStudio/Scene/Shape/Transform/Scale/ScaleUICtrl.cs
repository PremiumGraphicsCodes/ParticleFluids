using PG.CGStudio.Scene.Shape.Transform;
using PG.Core.Math;

namespace PG.CGStudio.UICtrl
{
    public class ScaleUICtrl : IUICtrl
    {
        private Vector2d prevPos = new Vector2d(0,0);

        private readonly ScaleModel model;

        public double Sensitivity { get; set; } = 1.0;

        public ScaleUICtrl(ScaleModel model)
        {
            this.model = model;
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
            var mainModel = MainModel.Instance;
            var diff = (position - prevPos) * Sensitivity;
            var matrix = PG.CLI.Command.Get<Matrix4d>(mainModel.World.Adapter, PG.GetLabels.CameraRotationMatrixLabel);
            var v = matrix * new Vector4d(diff.X, diff.Y, 0.0, 1.0);
            model.Scale.Value += new Vector3d(v.X, v.Y, v.Z);

            MainModel.Instance.World.Scenes.SetMatrix(model.Id.Value, model.ToMatrix());

            var canvas = Canvas3d.Instance;
            canvas.Update(MainModel.Instance.World);
            canvas.Render();

            this.prevPos = position;
        }

    }
}
