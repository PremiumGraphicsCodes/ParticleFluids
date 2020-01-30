using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.CLI;
using PG.Core.Math;
using PG.Scene;

namespace PGControlTest
{
    [TestClass]
    public class SceneListModelTest
    {
        [TestMethod]
        public void TestAddParticleSystemScene()
        {
            var adapter = new WorldAdapter();
            var scene = new SceneListModel(adapter);
            var positions = new List<Vector3d>();
            positions.Add(new Vector3d(0, 0, 0));
            var appearance = new PG.Core.UI.ParticleAppearance();
            var id = scene.AddParticleSystemScene(positions, "PS", appearance, 1);
            Assert.AreEqual(1, id);
        }
    }
}
