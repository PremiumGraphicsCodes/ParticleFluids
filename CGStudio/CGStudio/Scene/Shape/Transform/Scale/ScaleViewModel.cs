using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using PG.Core.Math;
using Prism.Regions;
using Reactive.Bindings;
using System;
using System.Reactive.Linq;

namespace PG.CGStudio.Scene.Shape.Transform.Scale
{
    public class ScaleViewModel : INavigationAware
    {
        private readonly ScaleModel model = new ScaleModel();

        public ReactiveProperty<int> ShapeId { get { return model.Id; } }

        public Vector3dViewModel CenterViewModel { get { return model.Center; } }

        public Vector3dViewModel RatioViewModel { get { return model.Scale; } }
        
        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        private readonly ScaleUICtrl scaleUICtrl;

        public ScaleViewModel()
        {
            var picker = new PickUICtrl(10, Core.SceneType.ShapeScene);
            picker.AddAction(OnSelected);
            Canvas3d.Instance.UICtrl = picker;

            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);
            this.scaleUICtrl = new ScaleUICtrl(model);
        }

        private void OnSelected(ObjectId id)
        {
            var center = MainModel.Instance.World.Scenes.GetCenter(id.parentId);
            this.CenterViewModel.Value = center;

            model.Id.Value = id.parentId;
            model.Center.Value = center;
            Canvas3d.Instance.UICtrl = scaleUICtrl;
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
