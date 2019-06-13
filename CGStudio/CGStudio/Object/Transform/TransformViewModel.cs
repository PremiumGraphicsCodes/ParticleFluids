using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Object.Transform
{
    public class TransformViewModel : BindableBase, INavigationAware
    {
        public SelectViewModel SelectViewModel { get; }

        public ReactiveCommand MoveCommand { get; }

        public ReactiveCommand ScaleCommand { get; }

        public ReactiveCommand RotateCommand { get; }

        public TransformViewModel()
        {
            SelectViewModel = new SelectViewModel();
            MoveCommand = new ReactiveCommand();
            MoveCommand.Subscribe(OnMove);
            ScaleCommand = new ReactiveCommand();
            ScaleCommand.Subscribe(OnScale);
            RotateCommand = new ReactiveCommand();
        }

        private void OnMove()
        {
            var moveCtrl = new ObjectMoveUICtrl(SelectViewModel.SelectedObjects);
            Canvas3d.Instance.UICtrl = moveCtrl;
        }

        private void OnScale()
        {
            var moveCtrl = new ObjectScaleUICtrl(SelectViewModel.SelectedObjects);
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
