using PG.Core.Shape;
using Reactive.Bindings;
using PG.Control.Math;
using Prism.Mvvm;
using PG.Control.OpenGL;

namespace PG.CGStudio.Generation.WireFrame
{
    public class CylinderGenerationViewModel : BindableBase
    {
        public Cylinder3dViewModel CylinderViewModel { get; }
            = new Cylinder3dViewModel();

        public ReactiveProperty<int> UNum { get; }
            = new ReactiveProperty<int>(36);

        public AppearanceViewModel AppearanceViewModel { get; }
            = new AppearanceViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        private readonly World world;

        private readonly Canvas3d canvas;

        public CylinderGenerationViewModel(World world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new WireFrameBuilder();
            var cylinder = CylinderViewModel.Value;
            builder.Add(cylinder, this.UNum.Value);
            var wireFrame = builder.ToWireFrame();
            var newId = world.Scenes.AddWireFrameScene(wireFrame, "WFCylinder", AppearanceViewModel.Value, 1);
            canvas.Camera.Fit();

            canvas.BuildShader(world, newId);
            canvas.Render();
        }
    }
}
