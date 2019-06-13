using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;

namespace PGCoreTest.Math
{
    [TestClass]
    public class Matrix4dTest
    {
        private readonly double tolerance = 1.0e-9;

        [TestMethod]
        public void TestDeterminant()
        {
            {
                var matrix = new Matrix4d();
                Assert.AreEqual(1.0, matrix.Determinant, tolerance);
            }

            {
                var matrix = new Matrix4d(1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1);
                Assert.AreEqual(0.0, matrix.Determinant, tolerance);
            }
        }

        [TestMethod]
        public void TestTransposed()
        {
            {
                var matrix = new Matrix4d();
                var actual = matrix.Transposed;
                var expected = new Matrix4d();
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }

            {
                var matrix = new Matrix4d
                    (
                    0, 1, 2, 3,
                    10, 11, 12, 13,
                    20, 21, 22, 23,
                    30, 31, 32, 33
                    );
                var actual = matrix.Transposed;
                var expected = new Matrix4d
                    (
                    0, 10, 20, 30,
                    1, 11, 21, 31,
                    2, 12, 22, 32,
                    3, 13, 23, 33
                    );
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
        }

        /*
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

        [TestMethod]
        public void TestMultipy()
        {
            var matrix = new Matrix3d(2, 1, 3, 1, -1, 2, 1, 2, 1);
            var actual = matrix * matrix;
            var expected = new Matrix3d(8, 7, 11, 3, 6, 3, 5, 1, 8);
            Assert.IsTrue(expected.IsSame(actual, tolerance));
        }
                */

    }
}