﻿using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;

namespace PGCoreTest.Math
{
    [TestClass]
    public class Sphere3dTest
    {
        private readonly double tolerance = 1.0e-6;

        [TestMethod]
        public void TestGetPosition()
        {
            var sphere = new Sphere3d(1.0, new Vector3d(0, 0, 0));
            var expected = new Vector3d(0.0, 0.0, 1.0);
            var actual = sphere.GetPosition(1.0, 0.0, 0.0);
            Assert.IsTrue(expected.IsSame(actual, tolerance));

            expected = new Vector3d(0.0, 0.0, -1.0);
            actual = sphere.GetPosition(1.0, 0.5, 0.0);
            Assert.IsTrue(expected.IsSame(actual, tolerance));
        }

        [TestMethod]
        public void TestIsInside()
        {
            var sphere = new Sphere3d(10.0, new Vector3d(0, 0, 0));
            Assert.IsTrue( sphere.IsInside(new Vector3d(5.0, 0.0, 0.0)) );
            Assert.IsFalse(sphere.IsInside(new Vector3d(15.0, 0.0, 0.0)));

        }
    }
}