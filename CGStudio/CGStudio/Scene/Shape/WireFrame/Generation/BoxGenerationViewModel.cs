using PG.Core.Shape;
using Reactive.Bindings;
using PG.Control;
using PG.Control.Math;
using Prism.Mvvm;
using PG.Core.UI;
using PG.Core.Graphics;
using PG.Control.OpenGL;
using PG.Scene;

namespace PG.CGStudio.Generation.WireFrame
{
    public class BoxGenerationViewModel : BindableBase
    {
        public Box3dViewModel BoxViewModel { get; }

        public AppearanceViewModel AppearanceViewModel { get; }

        public ReactiveCommand GenerationCommand { get; }

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        public BoxGenerationViewModel(SceneList world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            this.BoxViewModel = new Box3dViewModel();
            this.AppearanceViewModel = new AppearanceViewModel();
            this.GenerationCommand = new ReactiveCommand();
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new WireFrameBuilder();
            var box = BoxViewModel.Value;
            builder.Add(box);
            var wireFrame = builder.ToWireFrame();
            var appearance = AppearanceViewModel.Value;

            var newId = world.AddWireFrameScene(wireFrame, "WFBox", appearance, 1);

            canvas.Camera.Fit();

            canvas.BuildShader(world, newId);
            canvas.Render();
        }
    }
}
