using PG.Control.Math;
using PG.Core.Shape;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.WireFrame
{
    public class EllipseGenerationViewModel : BindableBase
    {
        public Circle3dViewModel CircleViewModel { get; }
            = new Circle3dViewModel();

        public ReactiveProperty<int> UNum { get; }
            = new ReactiveProperty<int>(36);

        public AppearanceViewModel AppearanceViewModel { get; }
            = new AppearanceViewModel();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public EllipseGenerationViewModel()
        {
            OkCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            var circle = CircleViewModel.Value;
            var builder = new WireFrameBuilder();
            builder.Add(circle, UNum.Value);
            var shape = builder.ToWireFrame();
            var appearance = AppearanceViewModel.Value;
            MainModel.Instance.World.Scenes.AddWireFrameScene(shape, "WFCircle", appearance, 1);
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
        }
    }
}
