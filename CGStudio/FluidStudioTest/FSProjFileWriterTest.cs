using System;
using System.Collections.Generic;
using System.ComponentModel;
using FluidStudio;
using FluidStudio.FileIO;
using FluidStudio.Physics;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;
using PG.Scene;

namespace FluidStudioTest
{
    [TestClass]
    public class FSProjFileWriterTest
    {
        /*
        [TestMethod]
        public void TestWrite()
        {
            var model = new MainModel();
            var particles = new List<Vector3d>();
            particles.Add(new Vector3d(0, 0, 0));
            var world = new SceneList();
            var id = world.AddParticleSystemScene(particles, "", new PG.Core.UI.ParticleAppearance(), 1);
            var physicsScene = new SolverScene();
            var fluidScene = new FluidScene(model.Scenes, id, 1.0f, 1.0f, "Fluid01");
            physicsScene.Fluids.Add(fluidScene);
            model.PhysicsModel.Scenes.Add(physicsScene);
            var writer = new FSProjFileWriter();
            writer.Write(model, "TestWrite.fsproj");
        }
        */
    }
}
