using PG.Control;
using PG.Core.Shape;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.PolygonMesh
{
    public class SphereGenerationViewModel : BindableBase
    {
        private Sphere3dViewModel sphereViewModel;

        public ReactiveProperty<int> UNum { get; private set; }

        public ReactiveProperty<int> VNum { get; private set; }

        public ReactiveCommand ExecuteCommand { get; private set; }

        public Sphere3dViewModel SphereViewModel
        {
            get { return sphereViewModel; }
        }

        public SphereGenerationViewModel()
        {
            this.sphereViewModel = new Sphere3dViewModel();
            this.UNum = new ReactiveProperty<int>(24);
            this.VNum = new ReactiveProperty<int>(24);
            this.ExecuteCommand = new ReactiveCommand();
        }
  
        private void OnExecute()
        {
            var builder = new PolygonMeshBuilder();
            builder.Build(sphereViewModel.Sphere, UNum.Value, VNum.Value);
            MainModel.Instance.Add(builder.PolygonMesh);
        }
    }
}
