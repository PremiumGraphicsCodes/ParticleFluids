using System;
using FluidStudio.VDB;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Scene;

namespace FluidStudioTest
{
    [TestClass]
    public class VDBModelTest
    {
        [TestMethod]
        public void TestInit()
        {
            var world = new SceneList();
            var model = new VDBModel();
            var isOk = model.Init(world);
            Assert.IsTrue(isOk);
        }
    }
}
