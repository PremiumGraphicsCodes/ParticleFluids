using PG.CGStudio.Generation;
using Prism.Mvvm;

namespace PG.CGStudio
{
    public class PolygonGenerationViewModel : BindableBase
    {
        private SphereGenerationViewModel sphereGenerationViewModel;

        public SphereGenerationViewModel SphereGenerationViewModel { get { return sphereGenerationViewModel; } }

        public PolygonGenerationViewModel()
        {
            this.sphereGenerationViewModel = new SphereGenerationViewModel();
        }

    }
}
