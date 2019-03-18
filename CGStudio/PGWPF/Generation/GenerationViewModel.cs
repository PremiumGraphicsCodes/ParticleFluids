using PG.CGStudio.Generation.ParticleSystem;
using PG.CGStudio.Generation.WireFrame;

namespace PG.CGStudio.Generation
{
    public class GenerationViewModel
    {
        public GenerationViewModel()
        {
            ContentViewModel = new WireFrameGenerationViewModel();
        }

        public WireFrameGenerationViewModel ContentViewModel { get; }
    }
}
