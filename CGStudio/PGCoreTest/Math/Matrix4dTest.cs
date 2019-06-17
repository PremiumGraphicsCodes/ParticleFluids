﻿using System;
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
                var matrix = Matrix4d.Identity();
                Assert.AreEqual(1.0, matrix.Determinant, tolerance);
            }

            {
                var matrix = Matrix4d.Zero();
                Assert.AreEqual(0.0, matrix.Determinant, tolerance);
            }

            {
                var matrix = new Matrix4d
                    (
                    1, 1, 1, 1,
                    1, 1, 1, 1,
                    1, 1, 1, 1,
                    1, 1, 1, 1
                    );
                Assert.AreEqual(0.0, matrix.Determinant, tolerance);
            }
        }

        [TestMethod]
        public void TestTransposed()
        {
            {
                var matrix = Matrix4d.Identity();
                var actual = matrix.Transposed;
                var expected = Matrix4d.Identity();
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

        [TestMethod]
        public void TestInverse()
        {
            {
                var matrix = new Matrix4d();
                var actual = matrix.Inverse;
                var expected = Matrix4d.Identity();
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
        }

        [TestMethod]
        public void TestMultipyByScalar()
        {
            var matrix = new Matrix4d
                (
                1, 2, 3, 4,
                11, 12, 13, 14,
                21, 22, 23, 24,
                31, 32, 33, 34
                );
            var actual = matrix * 10;
            var expected = new Matrix4d
                (
                10, 20, 30, 40,
                110, 120, 130, 140,
                210, 220, 230, 240,
                310, 320, 330, 340
                );
            Assert.IsTrue(expected.IsSame(actual, tolerance));
        }

        [TestMethod]
        public void TestMultipy()
        {
            var lhs = new Matrix4d
                (
                1, 2, 3, 4,
                11, 12, 13, 14,
                21, 22, 23, 24,
                31, 32, 33, 34
                );
            var rhs = new Matrix4d
                (
                100, 200, 300, 400,
                110, 120, 130, 140,
                210, 220, 230, 240,
                310, 320, 330, 340
                );
            var actual = lhs * rhs;
            var expected = new Matrix4d
                (
                2190, 2380, 2570, 2760,
                9490, 10980, 12470, 13960,
                16790, 19580, 22370, 25160,
                24090, 28180, 32270, 36360
                );
            Assert.IsTrue(expected.IsSame(actual, tolerance));
        }

    }
}