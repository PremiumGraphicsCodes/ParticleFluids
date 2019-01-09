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
    }
}
