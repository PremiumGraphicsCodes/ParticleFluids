using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using PG.Core.Math;
using PG.Core.Shape;
using PG.Core.UI;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Shape.Transform
{
    public class TranslateViewModel
    {
        public ShapeSelectViewModel ShapeSelectViewModel { get; }
            = new ShapeSelectViewModel();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        public Vector3dViewModel Translate { get; }
            = new Vector3dViewModel();

        private readonly TranslateUICtrl uiCtrl;

        private int bbId = -1;

        public TranslateViewModel()
        {
            Canvas3d.Instance.UICtrl = ShapeSelectViewModel.Picker;
            ShapeSelectViewModel.Picker.AddAction(OnSelected);

            //this.ShapeId.Subscribe(OnSelected);
            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);

            this.uiCtrl = new TranslateUICtrl(this);
        }

        private void OnSelected(ObjectId id)
        {
            this.uiCtrl.Sensivity = 1.0;
            Canvas3d.Instance.UICtrl = this.uiCtrl;
            bbId = ShapeSelectViewModel.Picker.bbId;
        }

        public void SetMatrix(bool doRender)
        {
            MainModel.Instance.World.Scenes.SetMatrix(ShapeSelectViewModel.Id.Value, ToMatrix());

            if (doRender)
            {
                var canvas = Canvas3d.Instance;
                canvas.Update(MainModel.Instance.World);
                canvas.Render();
            }
        }

        public void Transform(bool doRender)
        {
            MainModel.Instance.World.Scenes.Transform(ShapeSelectViewModel.Id.Value, ToMatrix());

            if (doRender)
            {
                var canvas = Canvas3d.Instance;
                canvas.Update(MainModel.Instance.World);
                canvas.Render();
            }
        }

        public Matrix4d ToMatrix()
        {
            var t = Translate.Value;
            return new Matrix4d
                (
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                t.X, t.Y, t.Z, 1.0
                );
        }


        private void OnOk()
        {
            Transform(false);

            Translate.Value = new Vector3d(0, 0, 0);
            SetMatrix(true);

            MainModel.Instance.World.Scenes.Delete(bbId, true);
            var bb = MainModel.Instance.World.Scenes.GetBoundingBox(ShapeSelectViewModel.Id.Value);
            var builder = new WireFrameBuilder();
            builder.Add(bb);
            var appearance = new WireAppearance();
            appearance.Color = new Core.Graphics.ColorRGBA(1.0f, 0.0f, 0.0f, 0.0f);
            bbId = MainModel.Instance.World.Scenes.AddWireFrameScene(builder.ToWireFrame(), "", appearance, 0);
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
        }

        private void OnCancel()
        {
            Translate.Value = new Vector3d(0, 0, 0);
            SetMatrix(true);

            MainModel.Instance.World.Scenes.Clear(0);
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
            /*
            MainModel.Instance.World.Scenes.Delete(bbId, true);
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
            */
        }
    }
}
