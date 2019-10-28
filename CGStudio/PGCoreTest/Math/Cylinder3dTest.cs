using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;

namespace PGCoreTest.Math
{
    [TestClass]
    public class Cylinder3dTest
    {
        private double tolerance = 1.0e-9;

        [TestMethod]
        public void TestGetPosition()
        {
            var cylinder = new Cylinder3d();
            {
                var expected = Vector3d.UnitX();
                var actual = cylinder.GetPosition(1.0, 0.0, 0.0);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
            {
                var expected = new Vector3d(-1, 0, 0);
                var actual = cylinder.GetPosition(1.0, 0.5, 0.0);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
        }

        [TestMethod]
        public void TestCalculateDistance()
        {
            var position = new Vector3d(20.0, 0.0, 0.0);
            var cylinder = new Cylinder3d(10.0, 100.0, new Vector3d(0, 0, 0));
            var distance = cylinder.CalculateDistance(position);
            Assert.AreEqual(10.0, distance, 1.0e-12);
        }

        [TestMethod]
        public void TestIsInside()
        {
            var cylinder = new Cylinder3d(10.0, 100.0, new Vector3d(0, 0, 0));
            Assert.IsTrue( cylinder.IsInside(new Vector3d(5.0, 0.0, 0.0)) );
        }
    }
}
