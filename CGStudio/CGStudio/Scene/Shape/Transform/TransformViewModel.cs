using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Control.UI;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Object.Transform
{
    public class TransformViewModel : BindableBase
    {
        public SceneSelectViewModel SceneSelectViewModel { get; }

        public Matrix4dViewModel MatrixViewModel { get; }
            = new Matrix4dViewModel();

        public ReactiveCommand ApplyCommand { get; }
            = new ReactiveCommand();

        private readonly SceneList world;

        private readonly Canvas3d canvas;
        
        public TransformViewModel(SceneList world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            SceneSelectViewModel = new SceneSelectViewModel(world, canvas);
            ApplyCommand.Subscribe(OnApply);
        }

        private void OnApply()
        {
            var id = SceneSelectViewModel.Id.Value;
            var matrix = MatrixViewModel.Value;
            world.Transform(id, matrix);
            canvas.Update();
            canvas.Render();
        }
    }
}
