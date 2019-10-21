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
            /*
            command.SetArg(, id.parentId);
            command.SetArg("ChildId", id.childId);
            command.Execute(MainModel.Instance.Repository.Adapter);
            var position = command.GetResult<Vector3d>("Position");
            command.Clear();
                        */

            var sphere = new Sphere3d(SphereViewModel.Value.Radius, position);
            SphereViewModel.Value = sphere;
            var builder = new WireFrameBuilder();
            builder.Build(sphere, 24, 24);
            var appearance = new WireAppearance();
            appearance.Width = 1.0f;
            appearance.Color = new Core.Graphics.ColorRGBA(1.0f, 0.0f, 0.0f, 0.0f);

            MainModel.Instance.World.AddWireFrameScene(builder.WireFrame.Edges, "Item",appearance, true);
            /*
            var command = new PG.CLI.Command();
            command.Create(PG.WireFrameAddLabels.WireFrameAddLabel);
            command.SetArg(PG.WireFrameAddLabels.LinesLabel, builder.WireFrame.Edges);
            command.SetArg(PG.WireFrameAddLabels.IsItemLabel, true);
            command.SetArg(PG.WireFrameAddLabels.ColorLabel, new PG.Core.Graphics.ColorRGBA(1.0f, 0.0f, 0.0f, 0.0f));
            command.Execute(MainModel.Instance.World.Adapter);
            */

            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();

            Canvas3d.Instance.UICtrl = new CameraUICtrl();
        }
    }
}
