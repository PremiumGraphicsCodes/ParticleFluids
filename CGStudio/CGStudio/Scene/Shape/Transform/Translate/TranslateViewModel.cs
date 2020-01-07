using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using PG.Core.Math;
using Prism.Regions;
using Reactive.Bindings;
using System;

namespace PG.CGStudio.Scene.Shape.Transform
{
    public class TranslateViewModel : INavigationAware
    {
        public ReactiveProperty<int> ShapeId { get { return model.Id; } }

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        private readonly TranslateUICtrl translateUiCtrl;

        private readonly TranslateModel model = new TranslateModel();

        public Vector3dViewModel Translate { get { return model.Translate; } }

        public TranslateViewModel()
        {
            var picker = new PickUICtrl(10, Core.SceneType.ShapeScene);
            picker.AddAction(OnSelected);
            Canvas3d.Instance.UICtrl = picker;
           
            //this.ShapeId.Subscribe(OnSelected);
            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);

            this.translateUiCtrl = new TranslateUICtrl(model);
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
            this.ShapeId.Value = id.parentId;
            this.translateUiCtrl.Sensivity = 1.0;
            Canvas3d.Instance.UICtrl = this.translateUiCtrl;
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

            model.Translate.Value = new Vector3d(0, 0, 0);
        }
    }
}
