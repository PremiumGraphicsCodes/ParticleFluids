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

        private TranslateUICtrl uiCtrl;

        private readonly TranslateModel model = new TranslateModel();

        public Vector3dViewModel Translate { get { return model.Translate; } }

        public TranslateViewModel()
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
            var picker = new PickUICtrl(10, Core.SceneType.ShapeScene);
            picker.AddAction(OnSelected);
            Canvas3d.Instance.UICtrl = picker;

            //this.ShapeId.Subscribe(OnSelected);
            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);

            this.uiCtrl = new TranslateUICtrl(model);
        }

        private void OnSelected(ObjectId id)
        {
            if(id.parentId == 0)
            {
                return;
            }
            this.ShapeId.Value = id.parentId;
            this.uiCtrl.Sensivity = 1.0;
            Canvas3d.Instance.UICtrl = this.uiCtrl;
        }

        private void OnOk()
        {
            model.Transform(false);

            model.Translate.Value = new Vector3d(0, 0, 0);
            model.SetMatrix(true);
        }

        private void OnCancel()
        {
            model.Translate.Value = new Vector3d(0, 0, 0);
            model.SetMatrix(true);
        }
    }
}
