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
        public SceneSelectViewModel SelectViewModel { get; }

        public Sphere3dViewModel SphereViewModel { get; }

        public ReactiveCommand PickCommand { get; }

        public SphereRegionSelectViewModel()
        {
            SelectViewModel = new SceneSelectViewModel();
            SphereViewModel = new Sphere3dViewModel();
            PickCommand = new ReactiveCommand();
            PickCommand.Subscribe(OnPickUI);
        }

        private void OnPickUI()
        {
            var picker = new ObjectPickUICtrl(10, SceneType.AllScene)
            {
                Action = OnPicked
            };
            Canvas3d.Instance.UICtrl = picker;
        }

        private void OnPicked(ObjectId id)
        {
            var position = MainModel.Instance.Repository.Adapter.GetSceneAdapter().FindPositionById(id.parentId, id.childId);

            var sphere = new Sphere3d(SphereViewModel.Value.Radius, position);
            SphereViewModel.Value = sphere;
            var builder = new WireFrameBuilder();
            builder.Build(sphere, 24, 24);
            MainModel.Instance.Repository.Adapter.GetItemAdapter().AddWireFrameScene(builder.WireFrame.Edges, "Item");
            Canvas3d.Instance.Update(MainModel.Instance.Repository);
            Canvas3d.Instance.Render();

            Canvas3d.Instance.UICtrl = new CameraUICtrl(Canvas3d.Instance.Renderer.camera);
        }
    }
}
