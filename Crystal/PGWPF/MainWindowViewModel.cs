using PG.CGStudio.Generation.ParticleSystem;
using Prism.Mvvm;

namespace PG.CGStudio
{
    public class MainWindowViewModel : BindableBase
    {
        private ParticleSystemGenerationViewModel particleSystemGenerationViewModel;

        public ParticleSystemGenerationViewModel ParticleSystemGenerationViewModel
        {
            get { return particleSystemGenerationViewModel; }
        }

        public MainWindowViewModel()
        {
            this.particleSystemGenerationViewModel = new ParticleSystemGenerationViewModel();
        }
    }
}
