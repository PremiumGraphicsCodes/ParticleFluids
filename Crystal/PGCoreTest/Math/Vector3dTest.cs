using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;

namespace PGCoreTest
{
    [TestClass]
    public class Vector3dTest
    {
        private double tolerance = 1.0e-6;

        [TestMethod]
        public void TestLengthSquard()
        {
            var vector = new Vector3d(10.0, 0.0, 0.0);
            Assert.AreEqual(100.0, vector.LengthSquared);
        }

        [TestMethod]
        public void TestLength()
        {
            var vector = new Vector3d(10.0, 0.0, 0.0);
            Assert.AreEqual(10.0, vector.Length);
        }

        [TestMethod]
        public void TestNormalize()
        {
            var vector = new Vector3d(10.0, 0.0, 0.0);
            var expected = new Vector3d(1, 0, 0);
            var actual = vector.Normalized;
            Assert.IsTrue(expected.IsSame(actual, tolerance));
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

        [TestMethod]
        public void TestCross()
        {
            var x = new Vector3d(1, 0, 0);
            var y = new Vector3d(0, 1, 0);
            var z = new Vector3d(0, 0, 1);
            Assert.IsTrue(z.IsSame(x.Cross(y), tolerance));
            Assert.IsTrue(x.IsSame(y.Cross(z), tolerance));
            Assert.IsTrue(y.IsSame(z.Cross(x), tolerance));
        }
    }
}
