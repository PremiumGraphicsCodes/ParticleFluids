using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Shape;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Shape.PolygonMesh.Generation
{
    public class TorusGenerationViewModel : BindableBase
    {
        public Torus3dViewModel TorusViewModel { get; }
            = new Torus3dViewModel();

        public ReactiveProperty<int> UNum { get; }
            = new ReactiveProperty<int>(36);

        public ReactiveProperty<int> VNum { get; }
            = new ReactiveProperty<int>(36);

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        private readonly SceneList scenes;

        private readonly Canvas3d canvas;

        public TorusGenerationViewModel(SceneList scenes, Canvas3d canvas)
        {
            this.scenes = scenes;
            this.canvas = canvas;
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var torus = TorusViewModel.Value;
            var builder = new PolygonMeshBuilder();
            builder.Add(torus, UNum.Value, VNum.Value);
            var shape = builder.ToPolygonMesh();
            var newId = scenes.AddPolygonMeshScene(shape, "PMTorus", 1);

            canvas.Camera.Fit();

            canvas.BuildShader(scenes, newId);
            canvas.Render();

        }
    }
}
