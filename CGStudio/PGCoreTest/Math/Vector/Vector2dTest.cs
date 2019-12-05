using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;

namespace PGCoreTest.Math
{
    [TestClass]
    public class Vector2dTest
    {
        private readonly double tolerance = 1.0e-9;

        [TestMethod]
        public void TestLengthSquared()
        {
            var v = new Vector2d(10.0, 1.0);
            Assert.AreEqual(101.0, v.LengthSquared, tolerance);
        }

        [TestMethod]
        public void TestLength()
        {
            var v = new Vector2d(10.0, 1.0);
            var expected = System.Math.Sqrt(101);
            Assert.AreEqual(expected, v.Length, tolerance);
        }

        [TestMethod]
        public void TestNormalized()
        {
            var v = new Vector2d(10.0, 0.0);
            var expected = new Vector2d(1.0, 0.0);
            var actual = v.Normalized;
            Assert.IsTrue(expected.IsSame(actual, tolerance));
        }

        [TestMethod]
        public void TestDot()
        {
            var v1 = new Vector2d(10.0, 1.0);
            var v2 = new Vector2d(2.0, 5.0);
            Assert.AreEqual( 25, v1.Dot(v2), tolerance );
        }
    }
}
