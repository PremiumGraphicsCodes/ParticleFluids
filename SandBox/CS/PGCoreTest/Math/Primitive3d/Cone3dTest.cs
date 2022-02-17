using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;

namespace PGCoreTest.Math.Primitive3d
{
    [TestClass]
    public class Cone3dTest
    {
        private readonly double tolerance = 1.0e-12;

        [TestMethod]
        public void TestToCircleAt()
        {
            var cone = new Cone3d(10.0, 100.0, new Vector3d(0, 0, 0));

            {
                var actual = cone.ToCircleAt(0.0);
                var expected = new Circle3d(10.0, new Vector3d(0, 0, 0));
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }

            {
                var actual = cone.ToCircleAt(0.1);
                var expected = new Circle3d(9.0, new Vector3d(0, 0, 10));
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }

            {
                var actual = cone.ToCircleAt(1.0);
                var expected = new Circle3d(0.0, new Vector3d(0, 0, 100));
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
        }

        [TestMethod]
        public void TestGetPosition()
        {
            var cone = new Cone3d(10.0, 100.0, new Vector3d(0, 0, 0));

            {
                var actual = cone.GetPosition(1.0, 1.0, 1.0);
                var expected = new Vector3d(0, 0, 100);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
        }
    }
}