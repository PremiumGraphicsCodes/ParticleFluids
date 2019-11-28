using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;

namespace PGCoreTest.Math
{
    [TestClass]
    public class Circle3dTest
    {
        private readonly double tolerance = 1.0e-12;

        [TestMethod]
        public void TestGetPosition()
        {
            var circle = new Circle3d(new Vector3d(0, 0, 0), new Vector3d(1, 0, 0), new Vector3d(0, 1, 0));
            {
                var actual = circle.GetPosition(0.25);
                var expected = new Vector3d(0, 1, 0);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }

            {
                var actual = circle.GetPosition(0.75);
                var expected = new Vector3d(0, -1, 0);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
        }

        [TestMethod]
        public void TestNormal()
        {
            var circle = new Circle3d(new Vector3d(0, 0, 0), new Vector3d(1, 0, 0), new Vector3d(0, 1, 0));
            var actual = circle.Normal();
            var expected = new Vector3d(0, 0, 1);
            Assert.IsTrue(expected.IsSame(actual, tolerance));
        }
    }
}