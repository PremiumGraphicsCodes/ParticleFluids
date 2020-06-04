using PG.CGStudio.Generation.WireFrame;
using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Shape;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Shape.WireFrame.Generation
{
    public class TorusGenerationViewModel : BindableBase
    {
        public Torus3dViewModel TorusViewModel { get; }
            = new Torus3dViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public AppearanceViewModel AppearanceViewModel { get; }
            = new AppearanceViewModel();

        public ReactiveProperty<int> UNum { get; }
            = new ReactiveProperty<int>(36);

        public ReactiveProperty<int> VNum { get; }
            = new ReactiveProperty<int>(36);

        private readonly SceneList scene;

        private readonly Canvas3d canvas;

        public TorusGenerationViewModel(SceneList scene, Canvas3d canvas)
        {
            this.scene = scene;
            this.canvas = canvas;
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var torus = TorusViewModel.Value;
            var builder = new WireFrameBuilder();
            builder.Add(torus, UNum.Value, VNum.Value);
            var shape = builder.ToWireFrame();
            var newId = scene.AddWireFrameScene(shape, "WFTorus", AppearanceViewModel.Value, 1);

            canvas.Camera.Fit();

            canvas.BuildShader(scene, newId);
            canvas.Render();
        }
    }
}
