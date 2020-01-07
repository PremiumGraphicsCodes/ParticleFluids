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

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        public TranslateViewModel()
        {
            this.ShapeSelectViewModel.Id.Subscribe(OnSelected);
            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);

            this.VectorViewModel.X.Subscribe(OnChanged);
            this.VectorViewModel.Y.Subscribe(OnChanged);
            this.VectorViewModel.Z.Subscribe(OnChanged);
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

        private void OnSelected(int id)
        {
            var moveCtrl = new TranslateUICtrl(id);
            moveCtrl.Sensivity = 1.0;
            Canvas3d.Instance.UICtrl = moveCtrl;
        }

        private void OnChanged(double x)
        {
            MainModel.Instance.World.Scenes.SetMatrix(ShapeSelectViewModel.Id.Value, ToMatrix());

            var canvas = Canvas3d.Instance;
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
