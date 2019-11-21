using PG.Control.Math;
using PG.Core.Shape;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.WireFrame
{
    public class SphereGenerationViewModel : BindableBase
    {
        public ReactiveProperty<int> UNum { get; }

        public ReactiveProperty<int> VNum { get; }

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public Sphere3dViewModel SphereViewModel { get; }
            = new Sphere3dViewModel();

        public AppearanceViewModel AppearanceViewModel { get; }

        public SphereGenerationViewModel()
        {
            this.UNum = new ReactiveProperty<int>(36);
            this.VNum = new ReactiveProperty<int>(36);
            this.AppearanceViewModel = new AppearanceViewModel();
            this.GenerationCommand.Subscribe(OnExecute);
        }

        private void OnExecute()
        {
            var builder = new WireFrameBuilder();
            builder.Build(SphereViewModel.Value, UNum.Value, VNum.Value);
            MainModel.Instance.World.Scenes.AddWireFrameScene(builder.WireFrame, "WFSphere", AppearanceViewModel.Value);
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
        }
    }
}
