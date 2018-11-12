using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Math;

namespace PGCoreTest
{
    [TestClass]
    public class Vector3dTest
    {
        [TestMethod]
        public void TestLengthSquard()
        {
            var vector = new Vector3d(10.0, 0.0, 0.0);
            Assert.AreEqual( 100.0, vector.LengthSquared );
        }

        [TestMethod]
        public void TestLength()
        {
            var vector = new Vector3d(10.0, 0.0, 0.0);
            Assert.AreEqual(10.0, vector.Length);
        }

        [TestMethod]
        public void TestDot()
        {
            var v1 = new Vector3d(10.0, 0.0, 0.0);
            var v2 = new Vector3d(0.0, 10.0, 0.0);
            var v3 = new Vector3d(10.0, 0.0, 0.0);
            Assert.AreEqual(0.0,   v1.Dot(v2));
            Assert.AreEqual(100.0, v1.Dot(v3));
        }
    }
}
