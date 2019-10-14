using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using PG.Core.Math;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Selection
{
    public class CylinderRegionSelectViewModel : BindableBase
    {
        public ShapeSelectViewModel SelectViewModel { get; }
            = new ShapeSelectViewModel();

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
            var command = new PG.CLI.Command("GetPosition");
            command.SetArg("ParentId", id.parentId);
            command.SetArg("ChildId", id.childId);
            command.Execute(MainModel.Instance.Repository.Adapter);
            var position = command.GetResult<Vector3d>("Position");

            var cylinder = new Sphere3d(CylinderViewModel.Value.Radius, position);
            CylinderViewModel.Value = cylinder;
            var builder = new WireFrameBuilder();
            builder.Build(sphere, 24, 24);
            var appearance = new WireAppearance();

            var wfCommand = new PG.CLI.Command("AddWireFrame");
            wfCommand.SetArg("Lines", builder.WireFrame);
            wfCommand.SetArg("IsItem", true);
            wfCommand.Execute(MainModel.Instance.Repository.Adapter);

            Canvas3d.Instance.Update(MainModel.Instance.Repository);
            Canvas3d.Instance.Render();

            Canvas3d.Instance.UICtrl = new CameraUICtrl();
        }
    }
}
