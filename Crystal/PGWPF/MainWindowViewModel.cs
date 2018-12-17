using PG.App.Generation.PolygonMesh;
using PG.CGStudio.Generation.ParticleSystem;
using PG.CGStudio.Generation.PolygonMesh;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio
{
    public class MainWindowViewModel : BindableBase
    {
        public ReactiveCommand ParticleSystemGenerationCommand { get; private set; }

        public ReactiveCommand PolygonMeshGenerationCommand { get; private set; }

        public MainWindowViewModel()
        {
            this.ParticleSystemGenerationCommand = new ReactiveCommand();
            this.ParticleSystemGenerationCommand.Subscribe(OnParticleSystemGeneration);

            this.PolygonMeshGenerationCommand = new ReactiveCommand();
            this.PolygonMeshGenerationCommand.Subscribe(OnPolygonMeshGeneration);
        }

        private void OnParticleSystemGeneration()
        {
            var dialog = new ParticleSystemGenerationView();
            dialog.DataContext = new ParticleSystemGenerationViewModel();
            dialog.Show();
        }

        private void OnPolygonMeshGeneration()
        {
            var dialog = new PolygonMeshGenerationView();
            dialog.DataContext = new PolygonMeshGenerationViewModel();
            dialog.Show();
        }
    }
}
