using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using PG.Core.Math;
using Prism.Regions;
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

        private readonly ScaleUICtrl uiCtrl;

        public ScaleViewModel()
        {
            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);
            this.uiCtrl = new ScaleUICtrl(this);

            ShapeSelectViewModel.Id.Subscribe(OnSelected);
        }

        private void OnSelected(int id)
        {
            if (id == 0)
            {
                return;
            }

            var center = MainModel.Instance.World.Scenes.GetCenter(id);
            this.CenterViewModel.Value = center;

            CenterViewModel.Value = center;
            Canvas3d.Instance.UICtrl = uiCtrl;
        }

        private void OnOk()
        {
            Transform(false);

            RatioViewModel.Value = new Vector3d(1, 1, 1);
            CenterViewModel.Value = new Vector3d(0, 0, 0);
            SetMatrix(true);
        }

        private void OnCancel()
        {
            RatioViewModel.Value = new Vector3d(1, 1, 1);
            CenterViewModel.Value = new Vector3d(0, 0, 0);
            SetMatrix(true);
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
