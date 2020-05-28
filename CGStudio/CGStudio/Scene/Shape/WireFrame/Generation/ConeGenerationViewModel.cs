using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Shape;
using PG.Scene;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.WireFrame
{
    public class ConeGenerationViewModel
    {
        public Cone3dViewModel ConeViewModel { get; }

        public AppearanceViewModel AppearanceViewModel { get; }

        public ReactiveCommand GenerationCommand { get; }

        private readonly SceneListModel world;

        private readonly Canvas3d canvas;

        public ConeGenerationViewModel(SceneListModel world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            this.ConeViewModel = new Cone3dViewModel();
            this.AppearanceViewModel = new AppearanceViewModel();
            this.GenerationCommand = new ReactiveCommand();
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new WireFrameBuilder();
            var cone = ConeViewModel.Value;
            builder.Add(cone, 24);
            var wireFrame = builder.ToWireFrame();
            var appearance = AppearanceViewModel.Value;

            world.AddWireFrameScene(wireFrame, "WFCone", appearance, 1);
            world.Sync();
            canvas.Camera.Fit();

            canvas.Update();
            canvas.Render();
        }

    }
}
