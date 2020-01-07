using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core.Math;
using Prism.Regions;
using Reactive.Bindings;
using System;
using System.Reactive.Linq;

namespace PG.CGStudio.Scene.Shape.Transform.Scale
{
    public class ScaleViewModel : INavigationAware
    {
        public ShapeSelectViewModel ShapeSelectViewModel { get; }
            = new ShapeSelectViewModel();

        public Vector3dViewModel RatioViewModel { get; }
            = new Vector3dViewModel(new Vector3d(1,1,1));

        public ReactiveCommand ScaleCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        private Matrix4d ToMatrix()
        {
            return new Matrix4d
                (
                RatioViewModel.X.Value, 0.0, 0.0, 0.0,
                0.0, RatioViewModel.Y.Value, 0.0, 0.0,
                0.0, 0.0, RatioViewModel.Z.Value, 0.0,
                0.0, 0.0, 0.0, 1.0
                );
        }

        public ScaleViewModel()
        {
            this.ScaleCommand.Subscribe(OnScale);
            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);
        }

        private void OnScale()
        {
            Canvas3d.Instance.UICtrl = new ScaleUICtrl(ShapeSelectViewModel.Id.Value, RatioViewModel);

            RatioViewModel.X.Subscribe(OnChanged);
            RatioViewModel.Y.Subscribe(OnChanged);
            RatioViewModel.Z.Subscribe(OnChanged);
        }

        private void OnChanged(double x)
        {
            var center = MainModel.Instance.World.Scenes.GetCenter(ShapeSelectViewModel.Id.Value);

            var m1 = new Matrix4d
                (
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                -center.X, -center.Y, -center.Z, 1.0
                );

            var m2 = ToMatrix();

            var m3 = new Matrix4d
                (
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                center.X, center.Y, center.Z, 1.0
                );

            var m = m1 * m2 * m3;

            var canvas = Canvas3d.Instance;
            MainModel.Instance.World.Scenes.SetMatrix(ShapeSelectViewModel.Id.Value, m);

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
            RatioViewModel.Value = new Vector3d(1, 1, 1);
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
