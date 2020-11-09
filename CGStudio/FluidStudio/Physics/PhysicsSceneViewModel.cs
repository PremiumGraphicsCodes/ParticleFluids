﻿using Reactive.Bindings;
using Reactive.Bindings.Extensions;

namespace FluidStudio.Physics
{
    // enum でタイプを定義する．

    public enum PhysicsSceneType
    {
        Solver,
        Fluid,
        CSGBoundary,
    };

    public class PhysicsSceneViewModel
    {
        public ReactiveCollection<PhysicsSceneViewModel> Children { get; }
            = new ReactiveCollection<PhysicsSceneViewModel>();

        public ReadOnlyReactiveProperty<string> Name { get; }

        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public PhysicsSceneType SceneType { get; }

        public PhysicsSceneViewModel(PhysicsSolver scene)
        {
            this.SceneType = PhysicsSceneType.Solver;
            Name = scene.Name.ToReadOnlyReactiveProperty();
//            Id = scene.Id
            foreach(var f in scene.Fluids)
            {
                Children.Add(new PhysicsSceneViewModel(f));
            }
            foreach(var b in scene.CSGBoundaries)
            {
                Children.Add(new PhysicsSceneViewModel(b));
            }
        }

        public PhysicsSceneViewModel(FluidScene scene)
        {
            this.SceneType = PhysicsSceneType.Fluid;
            this.Id.Value = scene.Id;
            Name = scene.Name.ToReadOnlyReactiveProperty();
        }

        public PhysicsSceneViewModel(CSGBoundaryScene scene)
        {
            this.SceneType = PhysicsSceneType.CSGBoundary;
            this.Id.Value = scene.Id;
            Name = scene.Name.ToReadOnlyReactiveProperty();
        }
    }
}
