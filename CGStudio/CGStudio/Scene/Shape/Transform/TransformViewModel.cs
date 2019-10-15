using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core.Math;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;
using System.Collections.Generic;

namespace PG.CGStudio.Object.Transform
{
    public class TransformViewModel : BindableBase, INavigationAware
    {
        public ShapeSelectViewModel SelectViewModel { get; }
            = new ShapeSelectViewModel();

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
            OKCommand = new ReactiveCommand();
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
            var moveCtrl = new TranslateUICtrl(SelectViewModel.Id.Value);
            Canvas3d.Instance.UICtrl = moveCtrl;
        }

        private void OnScale()
        {
            var moveCtrl = new ScaleUICtrl(SelectViewModel.Id.Value);
            Canvas3d.Instance.UICtrl = moveCtrl;
        }

        private void OnOk()
        {
            var command = new PG.CLI.Command("Transform");
            command.SetArg("Id", SelectViewModel.Id.Value);
            //            command.SetArg("Matrix", MatrixViewModel.Value.ToArray());
            command.Execute(MainModel.Instance.Repository.Adapter);
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
