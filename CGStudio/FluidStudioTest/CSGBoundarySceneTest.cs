using System;
using FluidStudio.Physics;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;
using PG.Scene;

namespace FluidStudioTest
{
    [TestClass]
    public class CSGBoundarySceneTest
    {
        [TestMethod]
        public void TestConstruct()
        {
            var world = new SceneList();
            var box = new Box3d(new Vector3d(0, 0, 0), new Vector3d(10, 10, 10));
            var scene = new CSGBoundaryScene(world, "CSG", box);
            Assert.AreEqual(2, scene.Id);
        }
    }
}
