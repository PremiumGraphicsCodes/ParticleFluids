using PG.CGStudio.Generation.ParticleSystem;
using PG.CGStudio.Generation.PolygonMesh;
using Prism.Mvvm;

namespace PG.CGStudio
{
    public class MainWindowViewModel : BindableBase
    {
        private readonly ParticleSystemGenerationViewModel particleSystemGenerationViewModel;
        private readonly PolygonMeshGenerationViewModel polygonMeshGenerationViewModel;

        public ParticleSystemGenerationViewModel ParticleSystemGenerationViewModel
        {
            get { return particleSystemGenerationViewModel; }
        }

        public PolygonMeshGenerationViewModel PolygonMeshGenerationViewModel
        {
            get { return polygonMeshGenerationViewModel; }
        }

        public MainWindowViewModel()
        {
            this.particleSystemGenerationViewModel = new ParticleSystemGenerationViewModel();
            this.polygonMeshGenerationViewModel = new PolygonMeshGenerationViewModel();
        }
    }
}
