﻿using PG.CLI;
using PG.Scene;
using System.Collections.Generic;
using Labels = PG.FluidSimulationLabels;
using CreateLabels = PG.PhysicsSolverCreateLabels;
using UpdateLabels = PG.PhysicsSolverUpdateLabels;
using PG.Control.OpenGL;
using FluidStudio.VDB;
using FluidStudio.Physics.Fluid;
using FluidStudio.Physics.MeshBoundary;

namespace FluidStudio.Physics
{
    public class SolverScene : IPhysicsScene
    {
        public string Name { get; private set; } = "Solver01";

        public List<FluidScene> Fluids { get; private set; }
            = new List<FluidScene>();

        public List<CSGBoundaryScene> CSGBoundaries { get; private set; }
            = new List<CSGBoundaryScene>();

        public List<MeshBoundaryScene> MeshBoundaries { get; private set; }
            = new List<MeshBoundaryScene>();

        public float TimeStep { get; set; } = 0.03f;

        public int Id { get; private set; }

        public void Create(SceneList scenes, List<FluidScene> fluids, List<CSGBoundaryScene> boundaries, float timeStep, string name)
        {
            var command = new PhysicsCommand(CreateLabels.CommandNameLabel);
            command.Execute(scenes.Adapter);
            this.Id = command.GetResult<int>(CreateLabels.NewIdLabel);
            Update(scenes, fluids, boundaries, timeStep, name);
        }

        public void Update(SceneList world, List<FluidScene> fluids, List<CSGBoundaryScene> boundaries, float timeStep, string name)
        {
            this.Fluids = fluids;
            this.CSGBoundaries = boundaries;
            this.TimeStep = timeStep;
            this.Name = name;
            Reset(world);
        }

        public void Simulate(SceneList scenes, VDBModel vdb, int timeStep)
        {
            var command = new PhysicsCommand(Labels.CommandNameLabel);
            command.SetArg(Labels.SolverIdLabel, Id);
            command.Execute(scenes.Adapter);
        }
        
        public void Reset(SceneList world)
        {
            var fluidIds = new List<int>();
            foreach (var f in Fluids)
            {
                fluidIds.Add(f.Id);
            }
            var boundaryIds = new List<int>();
            foreach (var b in CSGBoundaries)
            {
                boundaryIds.Add(b.Id);
            }
            var meshIds = new List<int>();
            foreach(var m in MeshBoundaries)
            {
                meshIds.Add(m.Id);
            }

            var command = new PhysicsCommand(UpdateLabels.CommandNameLabel);
            command.SetArg(UpdateLabels.IdLabel, Id);
            command.SetArg(UpdateLabels.FluidSceneIdsLabel, fluidIds);
            command.SetArg(UpdateLabels.CSGBoundarySceneIdsLabel, boundaryIds);
            command.SetArg(UpdateLabels.MeshBoundarySceneIdsLabel, meshIds);
            command.SetArg(UpdateLabels.TimeStepLabel, TimeStep);
            command.SetArg(UpdateLabels.NameLabel, Name);
            command.Execute(world.Adapter);
        }
    }
}