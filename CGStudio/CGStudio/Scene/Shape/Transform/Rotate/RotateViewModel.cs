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

        public RotateViewModel()
        {
            this.RotateCommand.Subscribe(OnRotate);
            this.OkCommand.Subscribe(OnOk);
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
            var rx = AngleViewModel.X.Value / 180.0 * System.Math.PI;
            var ry = AngleViewModel.Y.Value / 180.0 * System.Math.PI;
            var rz = AngleViewModel.Z.Value / 180.0 * System.Math.PI;

            var matrix = Matrix3d.RotationZ(rz) * Matrix3d.RotationY(ry) * Matrix3d.RotationX(rx);

            var canvas = Canvas3d.Instance;
            var command = new PG.CLI.Command(TransformLabels.RotateCommandLabel);
            command.SetArg(TransformLabels.IdLabel, ShapeSelectViewModel.Id.Value);
            command.SetArg(TransformLabels.MatrixLabel, matrix);
            command.Execute(MainModel.Instance.World.Adapter);

            canvas.Update(MainModel.Instance.World);
            canvas.Render();
        }

        private void OnOk()
        {

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
