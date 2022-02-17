﻿using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;

namespace PGCoreTest.Math
{
    [TestClass]
    public class Matrix3dTest
    {
        private readonly double tolerance = 1.0e-9;

        [TestMethod]
        public void TestDeterminant()
        {
            {
                var matrix = new Matrix3d();
                Assert.AreEqual(1.0, matrix.Determinant(), tolerance);
            }

            {
                var matrix = new Matrix3d(1, 1, 1, 1, 1, 1, 1, 1, 1);
                Assert.AreEqual(0.0, matrix.Determinant(), tolerance);
            }
        }

        [TestMethod]
        public void TestTransposed()
        {
            {
                var matrix = new Matrix3d();
                var actual = matrix.Transposed();
                var expected = new Matrix3d();
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }

            {
                var matrix = new Matrix3d
                    (
                    0, 1, 2,
                    10, 11, 12,
                    20, 21, 22
                    );
                var actual = matrix.Transposed();
                var expected = new Matrix3d(0, 10, 20, 1, 11, 21, 2, 12, 22);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }            
        }

        [TestMethod]
        public void TestInverse()
        {
            {
                var matrix = new Matrix3d();
                var actual = matrix.Inverse();
                var expected = Matrix3d.Identity();
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
        }

        [TestMethod]
        public void TestMultipy()
        {
            var matrix = new Matrix3d
                (
                2, 1, 3,
                1,-1, 2,
                1, 2, 1
                );
            var actual = matrix * matrix;
            var expected = new Matrix3d
                (
                8, 7, 11,
                3, 6, 3,
                5, 1, 8
                );
            Assert.IsTrue(expected.IsSame(actual, tolerance));
        }

        [TestMethod]
        public void TestMutiplyWithVector()
        {
            var m = new Matrix3d
                (
                00, 01, 02,
                10, 11, 12,
                20, 21, 22
                );

            var v = new Vector3d(1, 2, 3);

            {
                var actual = m * v;
                var expected = new Vector3d(8, 68, 128);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }

            {
                var actual = v * m;
                var expected = new Vector3d(80, 86, 92);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
        }
    }
}