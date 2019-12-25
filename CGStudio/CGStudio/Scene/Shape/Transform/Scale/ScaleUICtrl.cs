using PG.Control.Math;
using PG.Core.Math;

namespace PG.CGStudio.UICtrl
{
    public class ScaleUICtrl : IUICtrl
    {
        private Vector2d prevPos = new Vector2d(0,0);

        private int shapeId = -1;

        private Vector3dViewModel vectorViewModel;

        public ScaleUICtrl()
        {
        }

        public ScaleUICtrl(int shapeId, Vector3dViewModel vectorViewModel)
        {
            this.shapeId = shapeId;
            this.vectorViewModel = vectorViewModel;
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
            var model = MainModel.Instance;
            var diff = (position - prevPos) * 0.1;
            var matrix = PG.CLI.Command.Get<Matrix4d>(model.World.Adapter, PG.GetLabels.CameraRotationMatrixLabel);
            var v = matrix * new Vector4d(diff.X, diff.Y, 0.0, 0.0);
            vectorViewModel.Value += new Vector3d(v.X, v.Y, v.Z);

            this.prevPos = position;

            var canvas = Canvas3d.Instance;
            var command = new PG.CLI.Command(TransformLabels.ScaleCommandLabel);
            command.SetArg(TransformLabels.IdLabel, shapeId);
            command.SetArg(TransformLabels.ScaleRatioLabel, vectorViewModel.Value);
            command.Execute(MainModel.Instance.World.Adapter);

            canvas.Update(MainModel.Instance.World);
            canvas.Render();
        }
    }
}
