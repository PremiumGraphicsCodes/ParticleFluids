using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using PG.Core.Math;
using PG.Core.Shape;
using PG.Core.UI;
using Prism.Regions;
using Reactive.Bindings;
using System;

namespace PG.CGStudio.Scene.Shape.Transform
{
    public class TranslateViewModel : INavigationAware
    {
        public ShapeSelectViewModel ShapeSelectViewModel { get; }
            = new ShapeSelectViewModel();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        private TranslateUICtrl uiCtrl;

        private readonly TranslateModel model = new TranslateModel();

        public TranslateModel Model { get { return model; } }

        public Vector3dViewModel Translate { get { return model.Translate; } }

        private int bbId = -1;

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
            Canvas3d.Instance.UICtrl = ShapeSelectViewModel.Picker;
            ShapeSelectViewModel.Picker.AddAction(OnSelected);

            //this.ShapeId.Subscribe(OnSelected);
            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);

            this.uiCtrl = new TranslateUICtrl(model);
        }

        private void OnSelected(ObjectId id)
        {
            this.uiCtrl.Sensivity = 1.0;
            Canvas3d.Instance.UICtrl = this.uiCtrl;
            model.Id = id.parentId;
            bbId = ShapeSelectViewModel.Picker.bbId;
        }

        private void OnOk()
        {
            model.Transform(false);

            model.Translate.Value = new Vector3d(0, 0, 0);
            model.SetMatrix(true);

            MainModel.Instance.World.Scenes.Delete(bbId, true);
            var bb = MainModel.Instance.World.Scenes.GetBoundingBox(model.Id);
            var builder = new WireFrameBuilder();
            builder.Add(bb);
            var appearance = new WireAppearance();
            appearance.Color = new Core.Graphics.ColorRGBA(1.0f, 0.0f, 0.0f, 0.0f);
            bbId = MainModel.Instance.World.Scenes.AddWireFrameScene(builder.ToWireFrame(), "", appearance, 0);
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
        }

        private void OnCancel()
        {
            model.Translate.Value = new Vector3d(0, 0, 0);
            model.SetMatrix(true);

            MainModel.Instance.World.Scenes.Delete(bbId, true);
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
        }
    }
}
