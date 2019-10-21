using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using PG.Core.Math;
using PG.Core.Shape;
using PG.Core.UI;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Selection
{
    public class CylinderRegionSelectViewModel : BindableBase
    {
        public Cylinder3dViewModel CylinderViewModel { get; }
            = new Cylinder3dViewModel();

        public ReactiveCommand PickCommand { get; }
            = new ReactiveCommand();

        public CylinderRegionSelectViewModel()
        {
            PickCommand.Subscribe(OnPickUI);
        }

        private void OnPickUI()
        {
            var picker = new PickUICtrl(10, SceneType.AllScene)
            {
                Action = OnPicked
            };
            Canvas3d.Instance.UICtrl = picker;
        }

        private void OnPicked(ObjectId id)
        {
            var position = MainModel.Instance.World.GetPosition(id);

            var cylinder = new Cylinder3d();
            CylinderViewModel.Value = cylinder;
            var builder = new WireFrameBuilder();
            builder.Build(cylinder, 24, 24);
            var appearance = new WireAppearance();
            appearance.Color = new Core.Graphics.ColorRGBA(1.0f, 0.0f, 0.0f, 0.0f);

            MainModel.Instance.World.Scenes.AddWireFrameScene(builder.WireFrame.Edges, "", appearance, true);

            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();

            Canvas3d.Instance.UICtrl = new CameraUICtrl();
        }
    }
}
