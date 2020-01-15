using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using PG.Core.Math;
using Prism.Regions;
using Reactive.Bindings;
using System;

namespace PG.CGStudio.Scene.Shape.Transform
{
    public class RotateViewModel : INavigationAware
    {
        public Vector3dViewModel AngleViewModel { get; }
            = new Vector3dViewModel();

        public Vector3dViewModel CenterViewModel { get; }
            = new Vector3dViewModel();

        public ReactiveProperty<int> ShapeId { get; }
            = new ReactiveProperty<int>();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        private RotateUICtrl uiCtrl;

        public RotateViewModel()
        {
        }

        private void OnSelected(ObjectId id)
        {
            if (id.parentId == 0)
            {
                return;
            }

            var center = MainModel.Instance.World.Scenes.GetCenter(id.parentId);
            //this.CenterViewModel.Value = center;

            ShapeId.Value = id.parentId;
            CenterViewModel.Value = center;
            Canvas3d.Instance.UICtrl = uiCtrl;
        }


        private void OnOk()
        {
            MainModel.Instance.World.Scenes.Transform(ShapeId.Value, ToMatrix());

            OnCancel();
        }

        private void OnCancel()
        {
            MainModel.Instance.World.Scenes.SetMatrix(ShapeId.Value, Matrix4d.Identity());
            var canvas = Canvas3d.Instance;
            canvas.Update(MainModel.Instance.World);
            canvas.Render();

            AngleViewModel.Value = new Vector3d(0, 0, 0);
        }


        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var picker = new PickUICtrl(10, Core.SceneType.ShapeScene);
            picker.AddAction(OnSelected);
            Canvas3d.Instance.UICtrl = picker;

            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);

            uiCtrl = new RotateUICtrl(this);
        }

        public void SetMatrix(bool doRender)
        {
            MainModel.Instance.World.Scenes.SetMatrix(ShapeId.Value, ToMatrix());

            if (doRender)
            {
                var canvas = Canvas3d.Instance;
                canvas.Update(MainModel.Instance.World);
                canvas.Render();
            }
        }

        public void Transform(bool doRender)
        {
            MainModel.Instance.World.Scenes.Transform(ShapeId.Value, ToMatrix());

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
            var m1 = new Matrix4d
                (
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                -center.X, -center.Y, -center.Z, 1.0
                );

            var rx = AngleViewModel.X.Value / 180.0 * System.Math.PI;
            var ry = AngleViewModel.Y.Value / 180.0 * System.Math.PI;
            var rz = AngleViewModel.Z.Value / 180.0 * System.Math.PI;

            var rot = Matrix3d.RotationZ(rz) * Matrix3d.RotationY(ry) * Matrix3d.RotationX(rx);
            var m2 = new Matrix4d(rot);

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
