using System;
using System.Collections.Generic;
using FluidStudio.Physics;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;
using PG.Scene;

namespace FluidStudioTest
{
    [TestClass]
    public class FluidSceneTest
    {
        [TestMethod]
        public void TestConstruct()
        {
            var world = new SceneList();
            var particles = new List<Vector3d>();
            particles.Add(new Vector3d(0, 0, 0));
            var id = world.AddParticleSystemScene(particles, "", new PG.Core.UI.ParticleAppearance(), 1);
            var scene0 = new FluidScene(world, id, 1.0f, 1.0f);
            Assert.AreEqual(3, scene0.Id);
            var scene1 = new FluidScene(world, id, 1.0f, 1.0f);
            Assert.AreEqual(4, scene1.Id);

        }
    }
}
