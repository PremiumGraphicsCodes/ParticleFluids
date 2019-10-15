using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using Prism.Mvvm;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.CGStudio.Selection
{
    public class BoxRegionSelectViewModel : BindableBase
    {
        public Box3dViewModel BoxViewModel { get; }
            = new Box3dViewModel();

        public ReactiveCommand PickCommand { get; }
            = new ReactiveCommand();

        public BoxRegionSelectViewModel()
        {
     //       this.PickCommand.Subscribe()
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
            /*
            var command = new PG.CLI.Command("GetPosition");
            command.SetArg("ParentId", id.parentId);
            command.SetArg("ChildId", id.childId);
            command.Execute(MainModel.Instance.Repository.Adapter);
            var position = command.GetResult<Vector3d>("Position");

            var cylinder = new Cylinder3d();
            CylinderViewModel.Value = cylinder;
            var builder = new WireFrameBuilder();
            builder.Build(cylinder, 24, 24);
            var appearance = new WireAppearance();

            var wfCommand = new PG.CLI.Command("AddWireFrame");
            wfCommand.SetArg("Lines", builder.WireFrame);
            wfCommand.SetArg("IsItem", true);
            wfCommand.Execute(MainModel.Instance.Repository.Adapter);

            Canvas3d.Instance.Update(MainModel.Instance.Repository);
            Canvas3d.Instance.Render();

            Canvas3d.Instance.UICtrl = new CameraUICtrl();
            */
        }
    }
}
