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

        public ScaleModel Model { get { return model; } }

        public ReactiveProperty<int> ShapeId { get { return model.Id; } }

        public Vector3dViewModel CenterViewModel { get { return model.Center; } }

        public Vector3dViewModel RatioViewModel { get { return model.Scale; } }
        
        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        private ScaleUICtrl uiCtrl;

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
            Canvas3d.Instance.UICtrl = uiCtrl;
        }

        private void OnOk()
        {
            model.Transform(false);

            model.Scale.Value = new Vector3d(1, 1, 1);
            model.Center.Value = new Vector3d(0, 0, 0);
            model.SetMatrix(true);
        }

        private void OnCancel()
        {
            model.Scale.Value = new Vector3d(1, 1, 1);
            model.Center.Value = new Vector3d(0, 0, 0);
            model.SetMatrix(true);
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
            this.uiCtrl = new ScaleUICtrl(model);
        }
    }
}
