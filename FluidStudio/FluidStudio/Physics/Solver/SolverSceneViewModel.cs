using PG.Scene;
using Prism.Regions;
using Reactive.Bindings;
using System;
using System.Collections.Generic;

namespace FluidStudio.Physics.Solver
{
    public class SolverSceneViewModel : INavigationAware
    {
        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("Solver01");

        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveProperty<float> EffectLength { get; }
            = new ReactiveProperty<float>(2.0f);

        public ReactiveProperty<float> TimeStep { get; }
            = new ReactiveProperty<float>(0.03f);

        public ReactiveCommand UpdateCommand { get; }
            = new ReactiveCommand();

        private SolverScene scene;

        private readonly SceneList world;

        public SolverSceneViewModel(SceneList world)
        {
            this.world = world;
            this.UpdateCommand.Subscribe(OnUpdate);
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
            this.EffectLength.Value = item.EffectLength;
            this.TimeStep.Value = item.TimeStep;
            this.scene = item;
        }

        private void OnUpdate()
        {
            if (scene == null)
            {
                return;
            }
            scene.EffectLength = EffectLength.Value;
            scene.TimeStep = TimeStep.Value;
            scene.Name = this.Name.Value;
        }
    }
}
