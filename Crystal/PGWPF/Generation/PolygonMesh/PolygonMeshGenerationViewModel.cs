using Prism.Mvvm;

namespace PG.CGStudio.Generation.PolygonMesh
{
    public class PolygonMeshGenerationViewModel : BindableBase
    {
        public SphereGenerationViewModel SphereGenerationViewModel { get; private set; }

        public PolygonMeshGenerationViewModel()
        {
            SphereGenerationViewModel = new SphereGenerationViewModel();
        }
    }
}
