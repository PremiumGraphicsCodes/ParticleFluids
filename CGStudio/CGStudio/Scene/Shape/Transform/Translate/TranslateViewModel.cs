using PG.CGStudio.UICtrl;
using PG.Core;
using PG.Core.Math;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Shape.Transform
{
    public class TranslateViewModel : INavigationAware
    {
        public ReactiveProperty<int> ShapeId { get; }
            = new ReactiveProperty<int>();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        private TranslateUICtrl translateUiCtrl;

        public TranslateViewModel()
        {
            var picker = new PickUICtrl(10, Core.SceneType.ShapeScene);
            picker.AddAction(OnSelected);
            Canvas3d.Instance.UICtrl = picker;
           
            //this.ShapeId.Subscribe(OnSelected);
            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);
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

        private void OnSelected(ObjectId id)
        {
            if(id.parentId == 0)
            {
                return;
            }
            this.translateUiCtrl = new TranslateUICtrl(id.parentId);
            this.ShapeId.Value = id.parentId;
            this.translateUiCtrl.Sensivity = 1.0;
            Canvas3d.Instance.UICtrl = this.translateUiCtrl;
        }

        private void OnOk()
        {
            MainModel.Instance.World.Scenes.Transform(ShapeId.Value, translateUiCtrl.ToMatrix());
            OnCancel();
        }

        private void OnCancel()
        {
            MainModel.Instance.World.Scenes.SetMatrix(ShapeId.Value, Matrix4d.Identity());
            var canvas = Canvas3d.Instance;
            canvas.Update(MainModel.Instance.World);
            canvas.Render();

        }
    }
}
