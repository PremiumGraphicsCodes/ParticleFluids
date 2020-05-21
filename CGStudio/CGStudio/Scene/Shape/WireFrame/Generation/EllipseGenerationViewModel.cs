using PG.Control.Math;
using PG.Control.OpenGL;
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

        private readonly World world;

        private readonly Canvas3d canvas;

        public EllipseGenerationViewModel(World world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            OkCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            var circle = CircleViewModel.Value;
            var builder = new WireFrameBuilder();
            builder.Add(circle, UNum.Value);
            var shape = builder.ToWireFrame();
            var appearance = AppearanceViewModel.Value;

            world.Scenes.AddWireFrameScene(shape, "WFCircle", appearance, 1);
            world.Scenes.Sync();
            canvas.Camera.Fit();
            canvas.Update(world);
            canvas.Render();
        }
    }
}
