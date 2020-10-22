using PG.Control.OpenGL;
using PG.Control.UI;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;
using Labels = PG.FluidSceneCreateLabels;

namespace FluidStudio.Physics
{
    public class FluidViewModel : BindableBase
    {
        public SceneSelectViewModel ParticleSystemSelectViewModel { get; }

        public ReactiveProperty<double> Density { get; }
            = new ReactiveProperty<double>(1000.0);

        public ReactiveProperty<double> Stiffness { get; }
            = new ReactiveProperty<double>(100.0);

        public ReactiveProperty<double> Viscosity { get; }
            = new ReactiveProperty<double>(10.0);

        public ReactiveCommand AddCommand { get; }
            = new ReactiveCommand();

        public FluidViewModel(SceneList world, Canvas3d canvas)
        {
            this.ParticleSystemSelectViewModel = new SceneSelectViewModel(world, canvas);
            this.AddCommand.Subscribe(() => OnAdd(world));
            //this.GenerationCommand.Subscribe(() => OnGenerate(world, canvas));
        }

        private void OnAdd(SceneList world)
        {
            var command = new PG.CLI.PhysicsCommand(Labels.CommandNameLabel);
            command.SetArg(Labels.ParticleSystemIdLabel, this.ParticleSystemSelectViewModel.Id.Value);
            command.SetArg(Labels.NameLabel, "NewFluid");
            command.Execute(world.Adapter);
        }
    }
}
