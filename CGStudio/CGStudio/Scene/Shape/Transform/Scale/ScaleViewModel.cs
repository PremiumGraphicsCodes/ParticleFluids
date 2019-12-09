using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using Prism.Regions;
using Reactive.Bindings;

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

        public ReactiveCommand ApplyCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ScaleViewModel()
        {
            this.ScaleCommand.Subscribe(OnScale);
            this.ApplyCommand.Subscribe(OnApply);
            this.OkCommand.Subscribe(OnOk);
        }

        private void OnScale()
        {
            Canvas3d.Instance.UICtrl = new ScaleUICtrl(RatioViewModel);
        }

        private void OnApply()
        {
            var canvas = Canvas3d.Instance;
            var command = new PG.CLI.Command(TransformLabels.ScaleCommandLabel);
            command.SetArg(TransformLabels.IdLabel, ShapeSelectViewModel.Id.Value);
            command.SetArg(TransformLabels.ScaleRatioLabel, RatioViewModel.Value);
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
