using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core.Math;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Object.Transform
{
    public class TransformViewModel : BindableBase, INavigationAware
    {
        public ShapeSelectViewModel SelectViewModel { get; }
            = new ShapeSelectViewModel();

        public ReactiveCommand MoveCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand ScaleCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand RotateCommand { get; }
            = new ReactiveCommand();

        public Matrix4dViewModel MatrixViewModel { get; }
            = new Matrix4dViewModel();

        public ReactiveCommand OKCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        public TransformViewModel()
        {
            MoveCommand.Subscribe(OnMove);
            ScaleCommand.Subscribe(OnScale);
            RotateCommand.Subscribe(OnRotate);
            OKCommand.Subscribe(OnOk);
            MatrixViewModel.Value = new Matrix4d
                (
                1,0,0,0,
                0,1,0,0,
                0,0,1,0,
                0,0,0,1
                );
        }

        private void OnMove()
        {
            Canvas3d.Instance.UICtrl = new TranslateUICtrl(SelectViewModel.Id.Value);
        }

        private void OnScale()
        {
            Canvas3d.Instance.UICtrl = new ScaleUICtrl(SelectViewModel.Id.Value);
        }

        private void OnRotate()
        {
            Canvas3d.Instance.UICtrl = new RotateUICtrl(SelectViewModel.Id.Value);
        }

        private void OnOk()
        {
            var command = new PG.CLI.Command("Transform");
            command.SetArg("Id", SelectViewModel.Id.Value);
            //            command.SetArg("Matrix", MatrixViewModel.Value.ToArray());
            command.Execute(MainModel.Instance.World.Adapter);
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
