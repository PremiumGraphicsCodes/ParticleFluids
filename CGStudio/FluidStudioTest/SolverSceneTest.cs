using System;
using System.Collections.Generic;
using FluidStudio.Physics;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;
using PG.Scene;

namespace FluidStudioTest
{
    [TestClass]
    public class SolverSceneTest
    {
        private FluidScene CreateFluidTestScene(SceneList world, string name)
        {
            var particles = new List<Vector3d>();
            particles.Add(new Vector3d(0, 0, 0));
            var id = world.AddParticleSystemScene(particles, "", new PG.Core.UI.ParticleAppearance(), 1);
            return new FluidScene(world, id, 1.0f, 1.0f, name, false);
        }

        private SolverScene CreateSolverTestScene(SceneList world, string name)
        {
            var fluids = new List<FluidScene>();
            fluids.Add(CreateFluidTestScene(world, "Fluid"));
            var boundaries = new List<CSGBoundaryScene>();

            var solver = new SolverScene();
            solver.Create(world, fluids, boundaries, 0.03f, name);
            return solver;
        }

        [TestMethod]
        public void TestCreate()
        {
            var world = new SceneList();
            var solver = CreateSolverTestScene(world, "");
            Assert.AreEqual(3, solver.Id);
        }

        [TestMethod]
        public void TestSimulate()
        {
            var world = new SceneList();
            var solver = CreateSolverTestScene(world, "");
            solver.Simulate(world);
        }
    }
}
