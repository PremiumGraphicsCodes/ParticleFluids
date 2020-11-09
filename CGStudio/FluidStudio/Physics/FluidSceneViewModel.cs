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
        public SceneSelectViewModel ParticleSystemSelectViewModel { get; }

        public ReactiveProperty<double> Density { get; }
            = new ReactiveProperty<double>(1000.0);

        public ReactiveProperty<float> Stiffness { get; }
            = new ReactiveProperty<float>(1.0f);

        public ReactiveProperty<float> Viscosity { get; }
            = new ReactiveProperty<float>(1.0f);

        public ReactiveProperty<bool> IsBoundary { get; }
            = new ReactiveProperty<bool>(false);

        public ReactiveCommand AddCommand { get; }
            = new ReactiveCommand();

        public FluidSceneViewModel(MainModel model, SceneList world, Canvas3d canvas)
        {
            this.ParticleSystemSelectViewModel = new SceneSelectViewModel(world, canvas);
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["Scene"] as FluidScene;
            if (item == null)
            {
                return;
            }
            Stiffness.Value = item.Stiffness;
            Viscosity.Value = item.Viscosity;
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
        }
    }
}
