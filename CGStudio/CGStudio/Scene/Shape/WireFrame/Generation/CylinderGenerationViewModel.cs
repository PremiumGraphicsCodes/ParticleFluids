using PG.Core.Shape;
using Reactive.Bindings;
using PG.Control.Math;
using Prism.Mvvm;

namespace PG.CGStudio.Generation.WireFrame
{
    public class CylinderGenerationViewModel : BindableBase
    {
        public Cylinder3dViewModel CylinderViewModel { get; }

        public ReactiveProperty<int> UNum { get; }

        public ReactiveProperty<int> VNum { get; }

        public AppearanceViewModel AppearanceViewModel { get; }

        public ReactiveCommand GenerationCommand { get; }

        public CylinderGenerationViewModel()
        {
            this.CylinderViewModel = new Cylinder3dViewModel();
            this.UNum = new ReactiveProperty<int>(36);
            this.VNum = new ReactiveProperty<int>(36);
            this.AppearanceViewModel = new AppearanceViewModel();
            this.GenerationCommand = new ReactiveCommand();
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new WireFrameBuilder();
            var cylinder = CylinderViewModel.Value;
            builder.Build(cylinder, 25, 25);
            var wireFrame = builder.WireFrame;
            MainModel.Instance.World.Scenes.AddWireFrameScene(wireFrame.Edges, "WFCylinder", AppearanceViewModel.Value, false);
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
        }
    }
}
