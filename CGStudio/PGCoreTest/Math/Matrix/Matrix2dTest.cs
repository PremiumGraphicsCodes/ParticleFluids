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

        [TestMethod]
        public void TestRow()
        {
            var m = new Matrix2d
                (
                00, 01,
                10, 11
                );
            {
                var actual = m.Row(0);
                var expected = new Vector2d(0, 1);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
            {
                var actual = m.Row(1);
                var expected = new Vector2d(10, 11);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
        }

        [TestMethod]
        public void TestColumn()
        {
            var m = new Matrix2d
                (
                00, 01,
                10, 11
                );
            {
                var actual = m.Column(0);
                var expected = new Vector2d(0, 10);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }

            {
                var actual = m.Column(1);
                var expected = new Vector2d(01, 11);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
        }

        [TestMethod]
        public void TestMutiply()
        {
            {
                var m1 = new Matrix2d(1, 2, 3, 4);
                var m2 = new Matrix2d(5, 6, 7, 8);
                var actual = m1 * m2;
                var expected = new Matrix2d(19, 22, 43, 50);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
        }

        [TestMethod]
        public void TestMutiplyWithVector()
        {
            var m = new Matrix2d
                (
                00, 01,
                10, 11
                );

            var v = new Vector2d(1, 2);

            {
                var actual = m * v;
                var expected = new Vector2d(2, 32);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }

            {
                var actual = v * m;
                var expected = new Vector2d(20, 23);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
        }
    }
}
