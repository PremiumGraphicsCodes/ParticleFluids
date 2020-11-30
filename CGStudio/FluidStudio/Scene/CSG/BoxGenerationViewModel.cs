using PG.Control.Graphics;
using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;

namespace FluidStudio.Scene.CSG
{
    class BoxGenerationViewModel : BindableBase
    {
        public Box3dViewModel BoxViewModel { get; }
            = new Box3dViewModel();

        public ColorRGBAViewModel ColorViewModel { get; }
            = new ColorRGBAViewModel();

        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("CSGBox");

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public BoxGenerationViewModel(SceneList world, Canvas3d canvas)
        {
            GenerationCommand.Subscribe(() => OnGenerate(world, canvas));
        }

        private void OnGenerate(SceneList world, Canvas3d canvas)
        {
            var box = BoxViewModel.Value;
            var color = ColorViewModel.Value;
            var newId = world.AddSolidScene(box, "", color, 1);
            canvas.Camera.Fit();
            canvas.BuildShader(world, newId);
            canvas.Render();
        }
    }
}
