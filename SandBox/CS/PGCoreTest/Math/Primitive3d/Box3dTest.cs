using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using PG.Core.Math;

namespace PGCoreTest.Math
{
    [TestClass]
    public class Box3dTest
    {
        private double tolerance = 1.0e-9;

        [TestMethod]
        public void TestVolume()
        {
            {
                var box = new Box3d();
                Assert.AreEqual(1.0, box.Volume, tolerance);
            }

            {
                var v1 = new Vector3d(0, 0, 0);
                var v2 = new Vector3d(10, 1, 1);
                var box = new Box3d(v1,v2);
                Assert.AreEqual(10.0, box.Volume, tolerance);
            }
        }

        [TestMethod]
        public void TestGetPosition()
        {
            var v1 = new Vector3d(0, 0, 0);
            var v2 = new Vector3d(10, 1, 1);
            var box = new Box3d(v1, v2);

            {
                var actual = box.GetPosition(0.0, 0.0, 0.0);
                var expected = new Vector3d(0.0, 0.0, 0.0);
                Assert.IsTrue( expected.IsSame(actual, tolerance) );

                actual = box.GetPosition(0.5, 0.0, 0.0);
                expected = new Vector3d(5, 0, 0);
                Assert.IsTrue(expected.IsSame(actual, tolerance));

                actual = box.GetPosition(0.5, 0.5, 0.0);
                expected = new Vector3d(5, 0.5, 0);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
        }

        [TestMethod]
        public void TestIsInside()
        {
            var v1 = new Vector3d(0, 0, 0);
            var v2 = new Vector3d(10, 10, 10);
            var box = new Box3d(v1, v2);

            Assert.IsTrue( box.IsInside(new Vector3d(5, 5, 5)));
            Assert.IsFalse( box.IsInside(new Vector3d(15, 5, 5)));

        }
    }
}
