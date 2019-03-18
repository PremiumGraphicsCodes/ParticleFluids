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
            this.ParticleSystemGenerationBoxCommand = new ReactiveCommand();
            this.ParticleSystemGenerationBoxCommand.Subscribe(OnParticleSystemGenerationBox);

            this.ParticleSystemGenerationSphereCommand = new ReactiveCommand();
            this.ParticleSystemGenerationSphereCommand.Subscribe(OnParticleSystemGenerationSphere);

            this.ParticleSystemGenerationCylinderCommand = new ReactiveCommand();
            this.ParticleSystemGenerationCylinderCommand.Subscribe(OnParticleSystemGenerationCylinder);

            this.WireFrameGenerationBoxCommand = new ReactiveCommand();
            this.WireFrameGenerationBoxCommand.Subscribe(OnWireFrameGenerationBox);

            this.WireFrameGenerationSphereCommand = new ReactiveCommand();
            this.WireFrameGenerationSphereCommand.Subscribe(OnWireFrameGenerationSphere);

            this.WireFrameGenerationCylinderCommand = new ReactiveCommand();
            this.WireFrameGenerationCylinderCommand.Subscribe(OnWireFrameGenerationCylinder);


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

        public ReactiveCommand ParticleSystemGenerationBoxCommand { get; }

        public ReactiveCommand ParticleSystemGenerationSphereCommand { get; }

        public ReactiveCommand ParticleSystemGenerationCylinderCommand { get; }

        public ReactiveCommand WireFrameGenerationBoxCommand { get; }

        public ReactiveCommand WireFrameGenerationSphereCommand { get; }

        public ReactiveCommand WireFrameGenerationCylinderCommand { get; }

        public ReactiveCommand PolygonMeshGenerationCommand { get; }

        public GenerationViewModel GenerationViewModel { get; }
            = new GenerationViewModel();

        private void OnParticleSystemGenerationBox()
        {
            var vm = new ParticleSystemGenerationViewModel();
            vm.ContentViewModel.Value = new Generation.ParticleSystem.BoxGenerationViewModel();
            GenerationViewModel.ContentViewModel.Value = vm;
        }

        private void OnParticleSystemGenerationSphere()
        {
            var vm = new ParticleSystemGenerationViewModel();
            vm.ContentViewModel.Value = new Generation.ParticleSystem.SphereGenerationViewModel();
            GenerationViewModel.ContentViewModel.Value = vm;
        }

        private void OnParticleSystemGenerationCylinder()
        {
            var vm = new ParticleSystemGenerationViewModel();
            vm.ContentViewModel.Value = new Generation.ParticleSystem.CylinderGenerationViewModel();
            GenerationViewModel.ContentViewModel.Value = vm;
        }

        private void OnWireFrameGenerationBox()
        {
            var vm = new WireFrameGenerationViewModel();
            vm.ContentViewModel.Value = new Generation.WireFrame.BoxGenerationViewModel();
            GenerationViewModel.ContentViewModel.Value = vm;
        }

        private void OnWireFrameGenerationSphere()
        {
            var vm = new WireFrameGenerationViewModel();
            vm.ContentViewModel.Value = new Generation.WireFrame.SphereGenerationViewModel();
            GenerationViewModel.ContentViewModel.Value = vm;
        }

        private void OnWireFrameGenerationCylinder()
        {
            var vm = new WireFrameGenerationViewModel();
            vm.ContentViewModel.Value = new Generation.WireFrame.CylinderGenerationViewModel();
            GenerationViewModel.ContentViewModel.Value = vm;
        }


        private void OnPolygonMeshGeneration()
        {
            GenerationViewModel.ContentViewModel.Value = new PolygonMeshGenerationViewModel();
        }
    }
}
