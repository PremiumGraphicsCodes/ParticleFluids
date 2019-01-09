using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;

namespace PGCoreTest.Math
{
    [TestClass]
    public class Matrix3dTest
    {
        private double tolerance = 1.0e-9;

        [TestMethod]
        public void TestDeterminant()
        {
            {
                var matrix = new Matrix3d();
                Assert.AreEqual(1.0, matrix.Determinant, tolerance);
            }

            {
                var matrix = new Matrix3d(1, 1, 1, 1, 1, 1, 1, 1, 1);
                Assert.AreEqual(0.0, matrix.Determinant, tolerance);
            }
        }

        [TestMethod]
        public void TestTransposed()
        {
            {
                var matrix = new Matrix3d();
                var actual = matrix.Transposed;
                var expected = new Matrix3d();
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }

            {
                var matrix = new Matrix3d(0, 1, 2, 10, 11, 12, 20, 21, 22);
                var actual = matrix.Transposed;
                var expected = new Matrix3d(0, 10, 20, 1, 11, 21, 2, 12, 22);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }            
        }

        [TestMethod]
        public void TestInverse()
        {
            {
                var matrix = new Matrix3d();
                var actual = matrix.Inverse;
                var expected = Matrix3d.Identity();
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
        }
    }
}
