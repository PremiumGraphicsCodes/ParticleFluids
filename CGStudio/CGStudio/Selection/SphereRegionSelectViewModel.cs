using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Selection
{
    public class SphereRegionSelectViewModel : BindableBase
    {
        public ObjectSelectViewModel SelectViewModel { get; }

        public Sphere3dViewModel SphereViewModel { get; }

        public ReactiveCommand PickCommand { get; }

        public SphereRegionSelectViewModel()
        {
            SelectViewModel = new ObjectSelectViewModel();
            SphereViewModel = new Sphere3dViewModel();
            PickCommand = new ReactiveCommand();
            PickCommand.Subscribe(OnPickUI);
        }

        private void OnPickUI()
        {
            var picker = new ObjectPickUICtrl(10, Core.Shape.ShapeType.All)
            {
                Action = OnPicked
            };
            Canvas3d.Instance.UICtrl = picker;
        }

        private void OnPicked(ObjectId id)
        {
            /*
            var obj = MainModel.Instance.Repository.Objects.FindObjectById(id.parentId);

            var sphere = new Sphere3d(1.0, obj.GetPosition(id.childId));
            SphereViewModel.Value = sphere;
            var builder = new WireFrameBuilder();
            builder.Build(sphere, 24, 24);
            MainModel.Instance.Repository.Items.Add(builder.WireFrame, new WireAppearance(), "Item");
            Canvas3d.Instance.Update(MainModel.Instance.Repository);
            Canvas3d.Instance.Render();

            Canvas3d.Instance.UICtrl = new CameraUICtrl(Canvas3d.Instance.Renderer.camera);
            */
        }
    }
}
