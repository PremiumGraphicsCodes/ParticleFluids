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

        public Vector3dViewModel CenterViewModel { get; }
            = new Vector3dViewModel(new Vector3d(0, 0, 0));

        public Vector3dViewModel RatioViewModel { get; }
            = new Vector3dViewModel(new Vector3d(1,1,1));

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        private ScaleUICtrl scaleUICtrl = new ScaleUICtrl();

        public ScaleViewModel()
        {
            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);
            this.ShapeSelectViewModel.Id.Subscribe(OnSelected);
        }

        private void OnSelected(int id)
        {
            var center = MainModel.Instance.World.Scenes.GetCenter(id);
            this.CenterViewModel.Value = center;

            scaleUICtrl.ShapeId = id;
            scaleUICtrl.Center = center;
            Canvas3d.Instance.UICtrl = scaleUICtrl;
        }

        private void OnOk()
        {
            MainModel.Instance.World.Scenes.Transform(ShapeSelectViewModel.Id.Value, scaleUICtrl.ToMatrix());

            //OnCancel();
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
