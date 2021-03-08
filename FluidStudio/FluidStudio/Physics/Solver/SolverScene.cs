using PG.CLI;
using PG.Scene;
using System.Collections.Generic;
using Labels = PG.FluidSimulationLabels;
using CreateLabels = PG.PhysicsSolverCreateLabels;
using UpdateLabels = PG.PhysicsSolverUpdateLabels;
using FluidStudio.VDB;
using Reactive.Bindings;

namespace FluidStudio.Physics
{
    public class SolverScene : IPhysicsScene
    {
        public string Name { get; set; } = "Solver01";

        private List<FluidScene> fluids { get; }
            = new List<FluidScene>();

        private List<CSGBoundaryScene> boundaries { get; }
            = new List<CSGBoundaryScene>();

        public IEnumerable<FluidScene> Fluids { get { return fluids; } }

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

        public void Add(CSGBoundaryScene b)
        {
            this.boundaries.Add(b);
            this.Children.Add(b);
        }

        public void Clear()
        {
            fluids.Clear();
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
                foreach (var f in fluids)
                {
                    if (f == scene)
                    {
                        f.Delete();
                    }
                }
                fluids.Remove(scene as FluidScene);
                Children.Remove(scene);
            }
            else if(scene is CSGBoundaryScene)
            {
                foreach(var b in boundaries)
                {
                    if(b == scene)
                    {
                        b.Delete();
                    }
                }
                boundaries.Remove(scene as CSGBoundaryScene);
                Children.Remove(scene);
            }
            Send();
        }

        public void Send()
        {
            var fluidIds = new List<int>();
            foreach (var f in fluids)
            {
                fluidIds.Add(f.Id);
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
