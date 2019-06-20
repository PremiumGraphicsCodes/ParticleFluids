﻿using System;
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
    }
}
