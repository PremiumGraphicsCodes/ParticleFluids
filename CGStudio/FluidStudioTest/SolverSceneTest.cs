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
            return new FluidScene(world, id, 1.0f, 1.0f, name);
        }

        [TestMethod]
        public void TestCreate()
        {
            var world = new SceneList();
            var fluids = new List<FluidScene>();
            fluids.Add(CreateFluidTestScene(world, "Fluid01"));
            var boundaries = new List<CSGBoundaryScene>();

            var solver = new SolverScene();
            solver.Create(world, fluids, boundaries, 0.03f, "Solver01");
            Assert.AreEqual(4, solver.Id);
        }
    }
}
