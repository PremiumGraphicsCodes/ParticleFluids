using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using Prism.Regions;
using Reactive.Bindings;

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

        public ReactiveCommand ApplyCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public TranslateViewModel()
        {
            this.TranslateCommand.Subscribe(OnTranslate);
            this.ApplyCommand.Subscribe(OnApply);
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
            var moveCtrl = new TranslateUICtrl(ShapeSelectViewModel.Id.Value);
            Canvas3d.Instance.UICtrl = moveCtrl;
        }

        private void OnApply()
        {
            var canvas = Canvas3d.Instance;
            var command = new PG.CLI.Command(PG.TransformLabels.TranslateCommandLabel);
            command.SetArg(PG.TransformLabels.IdLabel, ShapeSelectViewModel.Id.Value);
            command.SetArg(PG.TransformLabels.TranslateLabel, VectorViewModel.Value);
            command.Execute(MainModel.Instance.World.Adapter);

            canvas.Update(MainModel.Instance.World);
            canvas.Render();
        }
    }
}
