using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core.Math;
using Prism.Regions;
using Reactive.Bindings;
using System;

namespace PG.CGStudio.Scene.Shape.Transform
{
    public class RotateViewModel : INavigationAware
    {
        public ShapeSelectViewModel ShapeSelectViewModel { get; }
            = new ShapeSelectViewModel();

        public Vector3dViewModel AngleViewModel { get; }
            = new Vector3dViewModel();

        public ReactiveCommand RotateCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        public RotateViewModel()
        {
            this.RotateCommand.Subscribe(OnRotate);
            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);
        }

        private void OnRotate()
        {
            Canvas3d.Instance.UICtrl = new RotateUICtrl(AngleViewModel);
            AngleViewModel.X.Subscribe(OnChanged);
            AngleViewModel.Y.Subscribe(OnChanged);
            AngleViewModel.Z.Subscribe(OnChanged);
        }

        private void OnChanged(double x)
        {
            var canvas = Canvas3d.Instance;
            MainModel.Instance.World.Scenes.SetMatrix(ShapeSelectViewModel.Id.Value, ToMatrix());

            canvas.Update(MainModel.Instance.World);
            canvas.Render();
        }

        private void OnOk()
        {
            MainModel.Instance.World.Scenes.Transform(ShapeSelectViewModel.Id.Value, ToMatrix());

            OnCancel();
        }

        private void OnCancel()
        {
            AngleViewModel.Value = new Vector3d(0, 0, 0);
        }

        private Matrix4d ToMatrix()
        {
            var rx = AngleViewModel.X.Value / 180.0 * System.Math.PI;
            var ry = AngleViewModel.Y.Value / 180.0 * System.Math.PI;
            var rz = AngleViewModel.Z.Value / 180.0 * System.Math.PI;

            var matrix = Matrix3d.RotationZ(rz) * Matrix3d.RotationY(ry) * Matrix3d.RotationX(rx);
            return new Matrix4d(matrix);
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
        }
    }
}
