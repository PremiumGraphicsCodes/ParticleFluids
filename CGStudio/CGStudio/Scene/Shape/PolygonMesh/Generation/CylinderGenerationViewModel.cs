using PG.Control.Math;
using PG.Core.Shape;
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

        public CylinderGenerationViewModel()
        {
            CylinderViewModel = new Cylinder3dViewModel();
            GenerateCommand = new ReactiveCommand();
            GenerateCommand.Subscribe(OnGenerate);
            UNum = new ReactiveProperty<int>(24);
            VNum = new ReactiveProperty<int>(24);
        }

        private void OnGenerate()
        {
            var builder = new PolygonMeshBuilder();
            builder.Build(CylinderViewModel.Value, UNum.Value, VNum.Value);
            MainModel.Instance.World.Scenes.AddPolygonMeshScene(builder, "PMCylinder");
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
        }
    }
}
