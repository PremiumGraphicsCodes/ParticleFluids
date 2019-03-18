using PG.CGStudio.Generation;
using PG.CGStudio.Generation.ParticleSystem;
using PG.CGStudio.Generation.PolygonMesh;
using PG.CGStudio.Generation.WireFrame;
using PG.CGStudio.Light;
using Prism.Mvvm;
using Reactive.Bindings;
using System.Windows;

namespace PG.CGStudio
{
    public class MainWindowViewModel : BindableBase
    {
        public MainWindowViewModel()
        {
            this.ParticleSystemGenerationCommand = new ReactiveCommand();
            this.ParticleSystemGenerationCommand.Subscribe(OnParticleSystemGeneration);

            this.WireFrameGenerationCommand = new ReactiveCommand();
            this.WireFrameGenerationCommand.Subscribe(OnWireFrameGeneration);

            this.PolygonMeshGenerationCommand = new ReactiveCommand();
            this.PolygonMeshGenerationCommand.Subscribe(OnPolygonMeshGeneration);


            LightListCommand = new ReactiveCommand();
            LightListCommand.Subscribe(OnShowLightList);
        }

        public ReactiveCommand LightListCommand { get; }

        private void OnShowLightList()
        {
            var dialog = new LightListView();
            dialog.Show();
        }

        public ReactiveCommand ParticleSystemGenerationCommand { get; }

        public ReactiveCommand WireFrameGenerationCommand { get; }

        public ReactiveCommand PolygonMeshGenerationCommand { get; }

        public GenerationViewModel GenerationViewModel { get; }
            = new GenerationViewModel();

        private void OnParticleSystemGeneration()
        {
            GenerationViewModel.ContentViewModel.Value = new ParticleSystemGenerationViewModel();
        }

        private void OnWireFrameGeneration()
        {
            GenerationViewModel.ContentViewModel.Value = new WireFrameGenerationViewModel();
        }

        private void OnPolygonMeshGeneration()
        {
            GenerationViewModel.ContentViewModel.Value = new PolygonMeshGenerationViewModel();
        }
    }
}
