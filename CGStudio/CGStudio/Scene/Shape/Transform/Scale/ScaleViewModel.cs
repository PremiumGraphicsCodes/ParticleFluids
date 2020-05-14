using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using PG.Core.Math;
using Reactive.Bindings;
using System;

namespace PG.CGStudio.Scene.Shape.Transform.Scale
{
    public class ScaleViewModel
    {
        public ShapeSelectViewModel ShapeSelectViewModel { get; }
            = new ShapeSelectViewModel();

        public Vector3dViewModel CenterViewModel { get; }
            = new Vector3dViewModel();

        public Vector3dViewModel RatioViewModel { get; }
            = new Vector3dViewModel(new Vector3d(1,1,1));

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        public ScaleViewModel()
        {
            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);

            this.ShapeSelectViewModel.Picker.AddAction(OnSelected);
        }

        private void OnSelected(ObjectId id)
        {
            if (id.parentId == 0)
            {
                return;
            }

            var center = World.Instance.Scenes.GetCenter(id.parentId);
            this.CenterViewModel.Value = center;
            HwndHostPresenter3d.Instance.Canvas.UICtrl = new ScaleUICtrl(this);
        }

        private void OnOk()
        {
            Transform(false);

            RatioViewModel.Value = new Vector3d(1, 1, 1);
            CenterViewModel.Value = new Vector3d(0, 0, 0);
            SetMatrix(true);

            World.Instance.Scenes.Clear(0);
            World.Instance.Scenes.ShowBoundingBox(ShapeSelectViewModel.Id.Value);
        }

        private void OnCancel()
        {
            RatioViewModel.Value = new Vector3d(1, 1, 1);
            CenterViewModel.Value = new Vector3d(0, 0, 0);
            SetMatrix(true);
        }

        public void SetMatrix(bool doRender)
        {
            World.Instance.Scenes.SetMatrix(ShapeSelectViewModel.Id.Value, ToMatrix());

            if (doRender)
            {
                var canvas = HwndHostPresenter3d.Instance;
                canvas.Update(World.Instance);
                canvas.Render();
            }
        }

        public void Transform(bool doRender)
        {
            World.Instance.Scenes.Transform(ShapeSelectViewModel.Id.Value, ToMatrix());

            if (doRender)
            {
                var canvas = HwndHostPresenter3d.Instance;
                canvas.Update(World.Instance);
                canvas.Render();
            }
        }

        public Matrix4d ToMatrix()
        {
            var center = CenterViewModel.Value;
            var scale = RatioViewModel.Value;

            var m1 = new Matrix4d
                (
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                -center.X, -center.Y, -center.Z, 1.0
                );

            var m2 = new Matrix4d
                (
                scale.X, 0.0, 0.0, 0.0,
                0.0, scale.Y, 0.0, 0.0,
                0.0, 0.0, scale.Z, 0.0,
                0.0, 0.0, 0.0, 1.0
                );

            var m3 = new Matrix4d
                (
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                center.X, center.Y, center.Z, 1.0
                );

            return m1 * m2 * m3;
        }
    }
}
