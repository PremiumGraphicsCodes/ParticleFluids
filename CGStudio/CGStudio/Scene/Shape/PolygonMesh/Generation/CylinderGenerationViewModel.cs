using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Shape;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.PolygonMesh
{
    public class CylinderGenerationViewModel : BindableBase
    {
        public Cylinder3dViewModel CylinderViewModel { get; }

        public ReactiveCommand GenerateCommand { get; }

        public ReactiveProperty<int> UNum { get; }

        public ReactiveProperty<int> VNum { get; }

        private readonly SceneListModel world;

        private readonly Canvas3d canvas;

        public CylinderGenerationViewModel(SceneListModel world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            CylinderViewModel = new Cylinder3dViewModel();
            GenerateCommand = new ReactiveCommand();
            GenerateCommand.Subscribe(OnGenerate);
            UNum = new ReactiveProperty<int>(24);
            VNum = new ReactiveProperty<int>(24);
        }

        private void OnGenerate()
        {
            var builder = new PolygonMeshBuilder();
            builder.Add(CylinderViewModel.Value, UNum.Value);

            world.AddPolygonMeshScene(builder.ToPolygonMesh(), "PMCylinder", 1);
            world.Sync();

            canvas.Camera.Fit();
            canvas.Update();
            canvas.Render();
        }
    }
}
