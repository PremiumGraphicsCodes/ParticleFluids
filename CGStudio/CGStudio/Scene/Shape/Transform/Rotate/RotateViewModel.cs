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

        public RotateModel Model { get { return model; } }

        public Vector3dViewModel AngleViewModel { get { return model.AngleViewModel; } }

        public Vector3dViewModel CenterViewModel { get { return model.CenterViewModel; } }

        public ReactiveProperty<int> ShapeId { get { return model.Id; } }

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        private RotateUICtrl uiCtrl;

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
            Canvas3d.Instance.UICtrl = uiCtrl;
        }


        private void OnOk()
        {
            MainModel.Instance.World.Scenes.Transform(ShapeId.Value, model.ToMatrix());

            OnCancel();
        }

        private void OnCancel()
        {
            MainModel.Instance.World.Scenes.SetMatrix(ShapeId.Value, Matrix4d.Identity());
            var canvas = Canvas3d.Instance;
            canvas.Update(MainModel.Instance.World);
            canvas.Render();

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

            uiCtrl = new RotateUICtrl(model);
        }
    }
}
