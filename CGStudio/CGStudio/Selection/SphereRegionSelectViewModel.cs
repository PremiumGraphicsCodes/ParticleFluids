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
    public class SphereRegionSelectViewModel : BindableBase
    {
        public Sphere3dViewModel SphereViewModel { get; }
            = new Sphere3dViewModel();

        public ReactiveCommand PickCommand { get; }
            = new ReactiveCommand();

        public SphereRegionSelectViewModel()
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
            var model = MainModel.Instance.World.Adapter;
            var position = PG.CLI.Command.Get(model, PG.GetLabels.PositionLabel, id.parentId, id.childId) as Vector3d;

            var sphere = new Sphere3d(SphereViewModel.Value.Radius, position);
            SphereViewModel.Value = sphere;
            var builder = new WireFrameBuilder();
            builder.Build(sphere, 24, 24);
            var appearance = new WireAppearance
            {
                Width = 1.0f,
                Color = new Core.Graphics.ColorRGBA(1.0f, 0.0f, 0.0f, 0.0f)
            };

            MainModel.Instance.World.Items.AddWireFrameScene(builder.WireFrame.Edges, "Item",appearance);

            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();

            Canvas3d.Instance.UICtrl = new CameraUICtrl();
        }
    }
}
