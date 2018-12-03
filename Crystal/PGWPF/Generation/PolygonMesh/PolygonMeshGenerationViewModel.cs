using PG.CGStudio.Generation;
using Prism.Mvvm;

namespace PG.CGStudio.Generation.PolygonMesh
{
    public class PolygonMeshGenerationViewModel : BindableBase
    {
        private SphereGenerationViewModel sphereGenerationViewModel;

        public SphereGenerationViewModel SphereGenerationViewModel { get { return sphereGenerationViewModel; } }

        public PolygonMeshGenerationViewModel()
        {
            this.sphereGenerationViewModel = new SphereGenerationViewModel();
        }

    }

}
