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

        public Sphere3dViewModel Sphere { get; }
            = new Sphere3dViewModel();

        public AppearanceViewModel Appearance { get; }

        public SphereGenerationViewModel()
        {
            this.UNum = new ReactiveProperty<int>(36);
            this.VNum = new ReactiveProperty<int>(36);
            this.Appearance = new AppearanceViewModel();
            this.GenerationCommand.Subscribe(OnExecute);
        }

        private void OnExecute()
        {
            var builder = new WireFrameBuilder();
            builder.Build(Sphere.Value, UNum.Value, VNum.Value);
            MainModel.Instance.Repository.AddWireFrameScene(builder.WireFrame.Edges, "WFSphere");
            Canvas3d.Instance.Update(MainModel.Instance.Repository);
            Canvas3d.Instance.Render();
        }
    }
}
