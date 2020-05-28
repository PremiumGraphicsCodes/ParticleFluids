using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Shape;
using PG.Scene;
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

        private readonly SceneListModel world;

        private readonly Canvas3d canvas;

        public EllipseGenerationViewModel(SceneListModel world, Canvas3d canvas)
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

            var newId = world.AddWireFrameScene(shape, "WFEllipse", appearance, 1);
            canvas.Camera.Fit();

            canvas.BuildShader(world, newId);
            canvas.Render();
        }
    }
}
