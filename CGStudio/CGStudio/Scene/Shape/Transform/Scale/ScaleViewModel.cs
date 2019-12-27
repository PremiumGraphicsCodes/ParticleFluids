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
            = new Vector3dViewModel(new Core.Math.Vector3d(1,1,1));

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
            var canvas = Canvas3d.Instance;
            var command = new PG.CLI.Command(SetMatrixLabels.CommandLabel);
            command.SetArg(SetMatrixLabels.IdLabel, ShapeSelectViewModel.Id.Value);
            command.SetArg(SetMatrixLabels.MatrixLabel, ToMatrix());
            command.Execute(MainModel.Instance.World.Adapter);

            canvas.Update(MainModel.Instance.World);
            canvas.Render();
        }

        private void OnOk()
        {
            var command = new PG.CLI.Command(TransformLabels.TransformCommandLabel);
            command.SetArg(TransformLabels.IdLabel, ShapeSelectViewModel.Id.Value);
            command.SetArg(TransformLabels.MatrixLabel, ToMatrix());
            command.Execute(MainModel.Instance.World.Adapter);

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
