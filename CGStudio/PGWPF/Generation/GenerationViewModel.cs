using PG.CGStudio.Generation.ParticleSystem;

namespace PG.CGStudio.Generation
{
    public class GenerationViewModel
    {
        public GenerationViewModel()
        {
            ContentViewModel = new ParticleSystemGenerationViewModel();
        }

        public ParticleSystemGenerationViewModel ContentViewModel { get; }
    }
}
