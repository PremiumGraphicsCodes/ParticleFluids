using PG.Core.Shape;
using Reactive.Bindings;
using PG.Control;
using PG.Control.Math;
using Prism.Mvvm;
using PG.Core.UI;
using PG.Core.Graphics;
using PG.Control.OpenGL;

namespace PG.CGStudio.Generation.WireFrame
{
    public class BoxGenerationViewModel : BindableBase
    {
        public Box3dViewModel BoxViewModel { get; }

        public AppearanceViewModel AppearanceViewModel { get; }

        public ReactiveCommand GenerationCommand { get; }

        private readonly World world;

        private readonly Canvas3d canvas;

        public BoxGenerationViewModel(World world, Canvas3d canvas)
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

            world.Scenes.AddWireFrameScene(wireFrame, "WFBox", appearance, 1);
            world.Scenes.Sync();

            canvas.Camera.Fit();
            canvas.Update(world);
            canvas.Render();
        }
    }
}
