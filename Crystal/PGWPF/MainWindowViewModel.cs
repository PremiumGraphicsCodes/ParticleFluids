using PG.CGStudio.Generation.ParticleSystem;
using PG.CGStudio.Generation.PolygonMesh;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio
{
    public class MainWindowViewModel : BindableBase
    {
        public ReactiveCommand ParticleSystemGenerationCommand { get; private set; }

        public MainWindowViewModel()
        {
            this.ParticleSystemGenerationCommand = new ReactiveCommand();
            this.ParticleSystemGenerationCommand.Subscribe(OnParticleSystemGeneration);
        }

        private void OnParticleSystemGeneration()
        {
            var dialog = new ParticleSystemGenerationView();
            dialog.DataContext = new ParticleSystemGenerationViewModel();
            dialog.Show();
        }
    }
}
