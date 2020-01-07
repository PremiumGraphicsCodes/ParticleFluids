using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using PG.Core.Math;
using Prism.Regions;
using Reactive.Bindings;
using System;

namespace PG.CGStudio.Scene.Shape.Transform
{
    public class RotateViewModel : INavigationAware
    {
        private readonly RotateModel model = new RotateModel();

        public Vector3dViewModel AngleViewModel { get { return model.AngleViewModel; } }

        public Vector3dViewModel CenterViewModel { get { return model.CenterViewModel; } }

        public ShapeSelectViewModel ShapeSelectViewModel { get; }
            = new ShapeSelectViewModel();

        public ReactiveProperty<int> ShapeId { get { return model.Id; } }

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        private RotateUICtrl UICtrl;

        public RotateViewModel()
        {
        }

        private void OnSelected(ObjectId id)
        {
            if (id.parentId == 0)
            {
                return;
            }

            var center = MainModel.Instance.World.Scenes.GetCenter(id.parentId);
            //this.CenterViewModel.Value = center;

            model.Id.Value = id.parentId;
            model.CenterViewModel.Value = center;
            Canvas3d.Instance.UICtrl = UICtrl;
        }


        private void OnOk()
        {
            MainModel.Instance.World.Scenes.Transform(ShapeSelectViewModel.Id.Value, model.ToMatrix());

            OnCancel();
        }

        private void OnCancel()
        {
            model.AngleViewModel.Value = new Vector3d(0, 0, 0);
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
            var picker = new PickUICtrl(10, Core.SceneType.ShapeScene);
            picker.AddAction(OnSelected);
            Canvas3d.Instance.UICtrl = picker;

            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);

            UICtrl = new RotateUICtrl(model);
        }
    }
}
