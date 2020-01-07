using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using PG.Core.Math;
using Prism.Regions;
using Reactive.Bindings;

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

        private ScaleUICtrl scaleUICtrl;

        public ScaleViewModel()
        {
        }

        private void OnSelected(ObjectId id)
        {
            if (id.parentId == 0)
            {
                return;
            }

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

            model.Scale.Value = new Vector3d(1, 1, 1);

            Canvas3d.Instance.UICtrl = new CameraUICtrl();
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
            this.scaleUICtrl = new ScaleUICtrl(model);
        }
    }
}
