using Prism.Regions;
using System;

namespace FluidStudio.Physics.Solver
{
    public class SolverSceneViewModel : INavigationAware
    {
        private SolverScene scene;

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["Scene"] as SolverScene;
            if (item == null)
            {
                return;
            }
            //Stiffness.Value = item.Stiffness;
            //Viscosity.Value = item.Viscosity;
            this.scene = item;
        }
    }
}
