using PG.CLI;
using PG.Scene;
using System.Collections.Generic;
using Reactive.Bindings;
using FluidStudio.Physics.Fluid;

using Labels = PG.FluidSimulationLabels;
using CreateLabels = PG.PhysicsSolverCreateLabels;
using UpdateLabels = PG.PhysicsSolverUpdateLabels;

namespace FluidStudio.Physics
{
    public class SolverScene : IPhysicsScene
    {
        public string Name { get; set; } = "Solver01";

        private List<FluidScene> fluids { get; }
            = new List<FluidScene>();

        private List<EmitterScene> emitters { get; }
            = new List<EmitterScene>();

        private List<CSGBoundaryScene> boundaries { get; }
            = new List<CSGBoundaryScene>();

        public IEnumerable<FluidScene> Fluids { get { return fluids; } }

        public IEnumerable<EmitterScene> Emitters { get { return emitters; } }

        public IEnumerable<CSGBoundaryScene> Boundaries { get { return boundaries; } }

        public ReactiveCollection<IPhysicsScene> Children { get; }
            = new ReactiveCollection<IPhysicsScene>();

        public float EffectLength { get; set; } = 2.0f;

        public float TimeStep { get; set; } = 0.03f;

        public int Id { get; private set; }

        public IPhysicsScene Parent { get; private set; }

        private readonly SceneList scenes;

        public SolverScene(SceneList scenes)
        {
            this.scenes = scenes;
            var command = new PhysicsCommand(CreateLabels.CommandNameLabel);
            command.Execute(scenes.Adapter);
            this.Id = command.GetResult<int>(CreateLabels.NewIdLabel);
        }

        public void Add(FluidScene f)
        {
            this.fluids.Add(f);
            this.Children.Add(f);
        }

        public void Add(EmitterScene e)
        {
            this.emitters.Add(e);
            this.Children.Add(e);
        }

        public void Add(CSGBoundaryScene b)
        {
            this.boundaries.Add(b);
            this.Children.Add(b);
        }

        public void Clear()
        {
            fluids.Clear();
            emitters.Clear();
            boundaries.Clear();
            Children.Clear();
        }

        public void Simulate()
        {
            var command = new PhysicsCommand(Labels.CommandNameLabel);
            command.SetArg(Labels.SolverIdLabel, Id);
            command.Execute(scenes.Adapter);
        }
        
        public void Delete(IPhysicsScene scene)
        {
            if (scene is FluidScene)
            {
                DeleteFluidScene(scene as FluidScene);
            }
            else if(scene is EmitterScene)
            {
                DeleteEmitterScene(scene as EmitterScene);
            }
            else if(scene is CSGBoundaryScene)
            {
                DeleteBoundaryScene(scene as CSGBoundaryScene);
            }
            Send();
        }

        private void DeleteFluidScene(FluidScene scene)
        {
            foreach (var f in fluids)
            {
                if (f == scene)
                {
                    f.Delete();
                }
            }
            fluids.Remove(scene);
            Children.Remove(scene);
        }

        private void DeleteEmitterScene(EmitterScene scene)
        {
            foreach (var e in emitters)
            {
                if (e == scene)
                {
                    e.Delete();
                }
            }
            emitters.Remove(scene);
            Children.Remove(scene);
        }

        private void DeleteBoundaryScene(CSGBoundaryScene scene)
        {
            foreach (var b in boundaries)
            {
                if (b == scene)
                {
                    b.Delete();
                }
            }
            boundaries.Remove(scene);
            Children.Remove(scene);
        }

        public void Send()
        {
            var fluidIds = new List<int>();
            foreach (var f in fluids)
            {
                fluidIds.Add(f.Id);
            }

            var emitterIds = new List<int>();
            foreach(var e in emitters)
            {
                emitterIds.Add(e.Id);
            }

            var csgIds = new List<int>();
            foreach (var csg in boundaries)
            {
                csgIds.Add(csg.Id);
            }

            var command = new PhysicsCommand(UpdateLabels.CommandNameLabel);
            command.SetArg(UpdateLabels.IdLabel, Id);
            command.SetArg(UpdateLabels.FluidSceneIdsLabel, fluidIds);
            command.SetArg(UpdateLabels.CSGBoundarySceneIdsLabel, csgIds);
            command.SetArg(UpdateLabels.MeshBoundarySceneIdsLabel, new List<int>());
            command.SetArg(UpdateLabels.EffectLengthLabel, EffectLength);
            command.SetArg(UpdateLabels.TimeStepLabel, TimeStep);
            command.SetArg(UpdateLabels.NameLabel, Name);
            command.Execute(scenes.Adapter);
        }

    }
}
