using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;

namespace PGCoreTest.Math
{
    [TestClass]
    public class Line3dTest
    {
        private readonly double tolerance = 1.0e-12;

        [TestMethod]
        public void TestLength()
        {
            var l = new Line3d(new Vector3d(0, 0, 0), new Vector3d(10, 0, 0));
            Assert.AreEqual(l.Length, 10.0);
        }

        [TestMethod]
        public void TestGetPosition()
        {
            var l = new Line3d(new Vector3d(0, 0, 0), new Vector3d(10, 0, 0));
            var actual = l.GetPosition(0.1);
            var expected = new Vector3d(1, 0, 0);
            Assert.IsTrue(expected.IsSame(actual, tolerance));
        }

        [TestMethod]
        public void TestDirection()
        {
            var l = new Line3d(new Vector3d(0, 0, 0), new Vector3d(10, 0, 0));
            var actual = l.Direction;
            var expected = new Vector3d(10, 0, 0);
            Assert.IsTrue(expected.IsSame(actual, tolerance));
        }

    }
}
