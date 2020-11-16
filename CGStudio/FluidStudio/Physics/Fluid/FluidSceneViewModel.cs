using PG.CGStudio.UICtrl;
using PG.Control.OpenGL;
using PG.Control.UI;
using PG.Scene;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace FluidStudio.Physics
{
    public class FluidSceneViewModel : INavigationAware
    {
        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("Fluid01");

        public SceneSelectViewModel ParticleSystemSelectViewModel { get; }

        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveProperty<double> Density { get; }
            = new ReactiveProperty<double>(1000.0);

        public ReactiveProperty<float> Stiffness { get; }
            = new ReactiveProperty<float>(1.0f);

        public ReactiveProperty<float> Viscosity { get; }
            = new ReactiveProperty<float>(1.0f);

        public ReactiveProperty<bool> IsBoundary { get; }
            = new ReactiveProperty<bool>(false);

        public ReactiveCommand UpdateCommand { get; }
            = new ReactiveCommand();

        private FluidScene scene;

        private SceneList world;

        public FluidSceneViewModel(MainModel model, SceneList world, Canvas3d canvas)
        {
            this.ParticleSystemSelectViewModel = new SceneSelectViewModel(world, canvas);
            this.UpdateCommand.Subscribe(OnUpdate);
            this.world = world;
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["Scene"] as FluidScene;
            if (item == null)
            {
                return;
            }
            this.Id.Value = item.Id;
            this.ParticleSystemSelectViewModel.Id.Value = item.ParticleSystemId;
            this.Stiffness.Value = item.Stiffness;
            this.Viscosity.Value = item.Viscosity;
            this.scene = item;
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
        }

        private void OnUpdate()
        {
            var particleSystemId = ParticleSystemSelectViewModel.Id.Value;
            var stiffness = Stiffness.Value;
            var viscosity = Viscosity.Value;
            var name = Name.Value;
            this.scene.Update(world, particleSystemId, stiffness, viscosity, name);
           // this.model.PhysicsModel.
        }
    }
}
