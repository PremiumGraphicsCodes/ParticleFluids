using PG.CLI;
using PG.Scene;
using System.Collections.Generic;
using Labels = PG.FluidSimulationLabels;
using CreateLabels = PG.PhysicsSolverCreateLabels;
using UpdateLabels = PG.PhysicsSolverUpdateLabels;
using FluidStudio.VDB;

namespace FluidStudio.Physics
{
    public class SolverScene : IPhysicsScene
    {
        public string Name { get; private set; } = "Solver01";

        public List<FluidScene> Fluids { get; private set; }
            = new List<FluidScene>();

        public List<CSGBoundaryScene> CSGBoundaries { get; private set; }
            = new List<CSGBoundaryScene>();

        public float EffectLength { get; set; } = 2.0f;

        public float TimeStep { get; set; } = 0.03f;

        public int Id { get; private set; }

        public IPhysicsScene Parent { get; private set; }

        private readonly SceneList scenes;

        public SolverScene(SceneList scenes)
        {
            this.scenes = scenes;
        }

        public void Clear()
        {
            Fluids.Clear();
        }

        public void Create(List<FluidScene> fluids, List<CSGBoundaryScene> csgBoundaries, float effectLength, float timeStep, string name)
        {
            var command = new PhysicsCommand(CreateLabels.CommandNameLabel);
            command.Execute(scenes.Adapter);
            this.Id = command.GetResult<int>(CreateLabels.NewIdLabel);
            Update(fluids, csgBoundaries, effectLength, timeStep, name);
        }

        public void Update(List<FluidScene> fluids, List<CSGBoundaryScene> cSGBoundaries, float effectLength, float timeStep, string name)
        {
            this.Fluids = fluids;
            this.CSGBoundaries = cSGBoundaries;
            this.EffectLength = effectLength;
            this.TimeStep = timeStep;
            this.Name = name;
        }

        public void Simulate(VDBModel vdb, int timeStep)
        {
            var command = new PhysicsCommand(Labels.CommandNameLabel);
            command.SetArg(Labels.SolverIdLabel, Id);
            command.Execute(scenes.Adapter);
        }
        
        public void Reset()
        {
            var fluidIds = new List<int>();
            foreach (var f in Fluids)
            {
                fluidIds.Add(f.Id);
            }

            var csgIds = new List<int>();
            foreach(var csg in CSGBoundaries)
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

        public void Delete(IPhysicsScene scene)
        {
            if (scene is FluidScene)
            {
                foreach (var f in Fluids)
                {
                    if (f == scene)
                    {
                        f.Delete();
                    }
                }
                Fluids.Remove(scene as FluidScene);
            }
            else if(scene is CSGBoundaryScene)
            {
                foreach(var b in CSGBoundaries)
                {
                    if(b == scene)
                    {
                        b.Delete();
                    }
                }
                CSGBoundaries.Remove(scene as CSGBoundaryScene);
            }
            Reset();
        }
    }
}
