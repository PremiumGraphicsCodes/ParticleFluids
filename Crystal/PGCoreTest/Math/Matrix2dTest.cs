using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;

namespace PGCoreTest.Math
{
    [TestClass]
    public class Matrix2dTest
    {
        private double tolerance = 1.0e-9;

        [TestMethod]
        public void TestDeterminant()
        {
            {
                var matrix = Matrix2d.Identity();
                Assert.AreEqual(1.0, matrix.Determinant, tolerance);
            }

            {
                var matrix = Matrix2d.Zero();
                Assert.AreEqual(0.0, matrix.Determinant, tolerance);
            }
        }

        [TestMethod]
        public void TestTransposed()
        {
            {
                var matrix = Matrix2d.Identity();
                var actual = matrix.Transposed;
                var expected = Matrix2d.Identity();
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }

            {
                var matrix = new Matrix2d(1, 2, 3, 4);
                var actual = matrix.Transposed;
                var expected = new Matrix2d(1, 3, 2, 4);
            }
        }
    }
}
