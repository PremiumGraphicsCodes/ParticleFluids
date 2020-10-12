using PG.Control.OpenGL;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;

namespace FluidStudio.Physics
{
    public class FluidViewModel : BindableBase
    {
        public ReactiveProperty<double> Density { get; }
            = new ReactiveProperty<double>(1000.0);

        public ReactiveProperty<double> Stiffness { get; }
            = new ReactiveProperty<double>(100.0);

        public ReactiveProperty<double> Viscosity { get; }
            = new ReactiveProperty<double>(10.0);

        public FluidViewModel(SceneList world, Canvas3d canvas)
        {
            //this.GenerationCommand.Subscribe(() => OnGenerate(world, canvas));
        }

    }
}
