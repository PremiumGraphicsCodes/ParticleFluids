using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;
using PG.Core.Shape;

namespace PGCoreTest.Shape
{
    [TestClass]
    public class WireFrameBuilderTest
    {
        [TestMethod]
        public void TestBuildBySphere()
        {
            var builder = new WireFrameBuilder();
            var sphere = new Sphere3d(1.0, new Vector3d(0,0,0));
            builder.Add(sphere, 10, 10);
            var actual = builder.ToWireFrame();
//            Assert.AreEqual()
        }
    }
}
