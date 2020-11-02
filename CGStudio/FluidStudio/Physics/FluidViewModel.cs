using PG.CGStudio.UICtrl;
using PG.Control.OpenGL;
using PG.Control.UI;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;

namespace FluidStudio.Physics
{
    public class FluidViewModel : BindableBase
    {
        public SceneSelectViewModel ParticleSystemSelectViewModel { get; }

        public ReactiveProperty<double> Density { get; }
            = new ReactiveProperty<double>(1000.0);

        public ReactiveProperty<float> Stiffness { get; }
            = new ReactiveProperty<float>(100.0f);

        public ReactiveProperty<float> Viscosity { get; }
            = new ReactiveProperty<float>(10.0f);

        public ReactiveCommand AddCommand { get; }
            = new ReactiveCommand();

        public FluidViewModel(MainModel model, SceneList world, Canvas3d canvas)
        {
            this.ParticleSystemSelectViewModel = new SceneSelectViewModel(world, canvas);
            this.AddCommand.Subscribe(() => OnAdd(model, world, canvas));
            //this.GenerationCommand.Subscribe(() => OnGenerate(world, canvas));
        }

        private void OnAdd(MainModel model, SceneList world, Canvas3d canvas)
        {
            var particleSystemId = ParticleSystemSelectViewModel.Id.Value;
            var stiffness = Stiffness.Value;
            var viscosity = Viscosity.Value;
            var scene = new FluidScene(world, canvas, particleSystemId, stiffness, viscosity);
            var fScene = new PhysicsScene();
            fScene.Fluids.Add(scene);
            model.PhysicsModel.Scenes.Add(fScene);

            canvas.UICtrl = new CameraUICtrl(world, canvas);
        }
    }
}
