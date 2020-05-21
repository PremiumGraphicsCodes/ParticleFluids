using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Shape;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.WireFrame
{
    public class SphereGenerationViewModel : BindableBase
    {
        public ReactiveProperty<int> UNum { get; }
            = new ReactiveProperty<int>(36);

        public ReactiveProperty<int> VNum { get; }
            = new ReactiveProperty<int>(36);

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public Sphere3dViewModel SphereViewModel { get; }
            = new Sphere3dViewModel();

        public AppearanceViewModel AppearanceViewModel { get; }
            = new AppearanceViewModel();

        private readonly World world;

        private readonly Canvas3d canvas;

        public SphereGenerationViewModel(World world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            this.GenerationCommand.Subscribe(() => OnExecute(world));
        }

        private void OnExecute(World world)
        {
            var builder = new WireFrameBuilder();
            builder.Add(SphereViewModel.Value, UNum.Value, VNum.Value);

            var newId = world.Scenes.AddWireFrameScene(builder.ToWireFrame(), "WFSphere", AppearanceViewModel.Value, 1);
            canvas.Camera.Fit();

            canvas.BuildShader(world, newId);
            canvas.Render();
        }
    }
}
