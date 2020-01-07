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

        private readonly ScaleModel model = new ScaleModel();

        public Vector3dViewModel CenterViewModel { get { return model.Center; } }

        public Vector3dViewModel RatioViewModel { get { return model.Scale; } }
        
        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        private readonly ScaleUICtrl scaleUICtrl;

        public ScaleViewModel()
        {
            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);
            this.ShapeSelectViewModel.Id.Subscribe(OnSelected);
            this.scaleUICtrl = new ScaleUICtrl(model);
        }

        private void OnSelected(int id)
        {
            var center = MainModel.Instance.World.Scenes.GetCenter(id);
            this.CenterViewModel.Value = center;

            model.Id.Value = id;
            model.Center.Value = center;
            Canvas3d.Instance.UICtrl = scaleUICtrl;
        }

        private void OnOk()
        {
            MainModel.Instance.World.Scenes.Transform(ShapeSelectViewModel.Id.Value, model.ToMatrix());

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
