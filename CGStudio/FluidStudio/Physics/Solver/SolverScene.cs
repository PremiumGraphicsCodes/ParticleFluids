﻿using PG.CLI;
using PG.Scene;
using System.Collections.Generic;
using Labels = PG.FluidSimulationLabels;
using CreateLabels = PG.PhysicsSolverCreateLabels;
using UpdateLabels = PG.PhysicsSolverUpdateLabels;
using PG.Control.OpenGL;
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

        public float TimeStep { get; private set; } = 0.03f;

        public int Id { get; private set; }

        public bool DoExportVDB { get; set; }

        public string VDBExportDirectory { get; set; }

        public bool DoMakeMesh { get; set; }

        public bool DoExportOBJ { get; set; }

        public string OBJExportDirectory { get; set; }

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
            if(DoExportVDB)
            {
                var filePath = VDBExportDirectory + "/" + Name + "_" + timeStep.ToString() + ".vdb";
                ExportVDB(scenes, vdb, filePath);
            }
        }
        
        public void ExportVDB(SceneList world, VDBModel vdb, string filePath)
        {
            var ids = new List<int>();
            foreach(var fluid in Fluids)
            {
                ids.Add( fluid.Id );
            }
            vdb.Write(filePath, world, ids);
        }

        public void ConvertToMesh(SceneList world, VDBModel vdb, Canvas3d canvas)
        {
            foreach (var fluid in Fluids)
            {
                vdb.BuildMesh(fluid.Id, fluid.PolygonMeshId, world);
                canvas.SendShader(world, fluid.PolygonMeshId);
            }
            canvas.Render();
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

            var command = new PhysicsCommand(UpdateLabels.CommandNameLabel);
            command.SetArg(UpdateLabels.IdLabel, Id);
            command.SetArg(UpdateLabels.FluidSceneIdsLabel, fluidIds);
            command.SetArg(UpdateLabels.CSGBoundarySceneIdsLabel, boundaryIds);
            command.SetArg(UpdateLabels.TimeStepLabel, TimeStep);
            command.SetArg(UpdateLabels.NameLabel, Name);
            command.Execute(world.Adapter);
        }
    }
}
