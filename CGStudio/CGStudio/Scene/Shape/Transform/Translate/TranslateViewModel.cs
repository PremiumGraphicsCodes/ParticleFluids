using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core.Math;
using Prism.Regions;
using Reactive.Bindings;
using System;

namespace PG.CGStudio.Scene.Shape.Transform
{
    public class TranslateViewModel : INavigationAware
    {
        public ShapeSelectViewModel ShapeSelectViewModel { get; }
            = new ShapeSelectViewModel();

        public Vector3dViewModel VectorViewModel { get; }
            = new Vector3dViewModel();

        public ReactiveCommand TranslateCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        public TranslateViewModel()
        {
            this.TranslateCommand.Subscribe(OnTranslate);
            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);
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

        private void OnTranslate()
        {
            var moveCtrl = new TranslateUICtrl(VectorViewModel);
            moveCtrl.Sensivity = 1.0;
            Canvas3d.Instance.UICtrl = moveCtrl;
            VectorViewModel.X.Subscribe(OnChanged);
            VectorViewModel.Y.Subscribe(OnChanged);
            VectorViewModel.Z.Subscribe(OnChanged);
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
            VectorViewModel.Value = new Vector3d(0, 0, 0);
        }

        private Matrix4d ToMatrix()
        {
            return new Matrix4d
                (
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                VectorViewModel.X.Value, VectorViewModel.Y.Value, VectorViewModel.Z.Value, 1.0
                );
        }

    }
}
