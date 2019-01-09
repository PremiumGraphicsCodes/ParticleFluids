using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;

namespace PGCoreTest.Math
{
    [TestClass]
    public class Vector2dTest
    {
        private double tolerance = 1.0e-9;

        [TestMethod]
        public void TestMethod1()
        {
            var v = new Vector2d(10.0, 1.0);
            Assert.AreEqual(101.0, v.LengthSquared, tolerance);
        }
    }
}
