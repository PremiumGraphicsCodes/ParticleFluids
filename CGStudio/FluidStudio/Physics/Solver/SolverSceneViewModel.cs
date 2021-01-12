using PG.Scene;
using Prism.Regions;
using Reactive.Bindings;
using System;

namespace FluidStudio.Physics.Solver
{
    public class SolverSceneViewModel : INavigationAware
    {
        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("Solver01");

        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveProperty<float> TimeStep { get; }
            = new ReactiveProperty<float>(0.03f);

        private SolverScene scene;

        private readonly SceneList world;

        public SolverSceneViewModel(SceneList world)
        {
            this.world = world;
            this.Name.Subscribe(OnChangeName);
            this.TimeStep.Subscribe(OnChangeTimeStep);
        }

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
            this.Name.Value = item.Name;
            this.Id.Value = Id.Value;
            this.scene = item;
        }

        private void OnChangeName(string name)
        {
            OnUpdate();
        }

        private void OnChangeTimeStep(float dt)
        {
            OnUpdate();
        }

        private void OnUpdate()
        {
            if (scene == null)
            {
                return;
            }
            scene.Update(world, this.scene.Fluids, this.scene.CSGBoundaries, TimeStep.Value, this.Name.Value);
        }
    }
}
