using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;
using System.Collections.Generic;

namespace PG.CGStudio.Object.Transform
{
    public class TransformViewModel : BindableBase, INavigationAware
    {
        public SceneSelectViewModel SelectViewModel { get; }
            = new SceneSelectViewModel();

        public ReactiveCommand MoveCommand { get; }

        public ReactiveCommand ScaleCommand { get; }

        public ReactiveCommand RotateCommand { get; }

        public Matrix4dViewModel MatrixViewModel { get; }
            = new Matrix4dViewModel();

        public ReactiveCommand OKCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }

        public TransformViewModel()
        {
            MoveCommand = new ReactiveCommand();
            MoveCommand.Subscribe(OnMove);
            ScaleCommand = new ReactiveCommand();
            ScaleCommand.Subscribe(OnScale);
            RotateCommand = new ReactiveCommand();
        }

        private void OnMove()
        {
            var ids = new List<int>
            {
                SelectViewModel.Id.Value
            };
            var moveCtrl = new ObjectMoveUICtrl(ids);
            Canvas3d.Instance.UICtrl = moveCtrl;
        }

        private void OnScale()
        {
            var ids = new List<int>
            {
                SelectViewModel.Id.Value
            };
            var moveCtrl = new ObjectScaleUICtrl(ids);
            Canvas3d.Instance.UICtrl = moveCtrl;
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {

        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {

        }
    }
}
