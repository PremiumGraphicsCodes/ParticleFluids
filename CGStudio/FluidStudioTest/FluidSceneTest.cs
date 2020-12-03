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
        private FluidScene CreateTestScene(SceneList world, string name)
        {
            var particles = new List<Vector3d>();
            particles.Add(new Vector3d(0, 0, 0));
            var id = world.AddParticleSystemScene(particles, "", new PG.Core.UI.ParticleAppearance(), 1);
            var scene = new FluidScene();
            scene.Create(world, id, 1.0f, 1.0f, name, false);
            return scene;
        }

        [TestMethod]
        public void TestConstruct()
        {
            var world = new SceneList();
            var scene0 = CreateTestScene(world, "Fluid01");
            Assert.AreEqual(2, scene0.Id);
            var scene1 = CreateTestScene(world, "Fluid02");
            Assert.AreEqual(4, scene1.Id);
        }

        /*
        [TestMethod]
        public void TestReset()
        {

        }
        */
    }
}
