using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core;
using PG.Core.Math;
using PG.Core.Shape;
using PG.Core.UI;
using PG.Scene;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Shape.Transform
{
    public class TranslateViewModel
    {
        public ShapeSelectViewModel ShapeSelectViewModel { get; }

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        public Vector3dViewModel Translate { get; }
            = new Vector3dViewModel();

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        public TranslateViewModel(SceneList world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            this.ShapeSelectViewModel = new ShapeSelectViewModel(world, canvas);
            canvas.UICtrl = ShapeSelectViewModel.Picker;
            ShapeSelectViewModel.Picker.AddAction(OnSelected);

            //this.ShapeId.Subscribe(OnSelected);
            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);
        }

        private void OnSelected(ObjectId id)
        {
            var uiCtrl = new TranslateUICtrl(this, canvas);
            uiCtrl.Sensivity = 1.0;
            canvas.UICtrl = uiCtrl;
        }

        public void SetMatrix(bool doRender)
        {
            world.SetMatrix(ShapeSelectViewModel.Id.Value, ToMatrix());

            if (doRender)
            {
                canvas.Update();
                canvas.Render();
            }
        }

        public void Transform(bool doRender)
        {
            world.Transform(ShapeSelectViewModel.Id.Value, ToMatrix());

            if (doRender)
            {
                canvas.Update();
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

            world.Clear(0);
            world.ShowBoundingBox(ShapeSelectViewModel.Id.Value);
        }

        private void OnCancel()
        {
            Translate.Value = new Vector3d(0, 0, 0);
            SetMatrix(true);
        }
    }
}
