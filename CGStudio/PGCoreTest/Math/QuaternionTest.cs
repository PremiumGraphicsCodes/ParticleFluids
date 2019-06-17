using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;

namespace PGCoreTest.Math
{
    [TestClass]
    public class QuaternionTest
    {
        [TestMethod]
        public void TestFromRotationMatrix()
        {
            {
                var axis = new Vector3d(-1, 0, 0);
                var angle = System.Math.PI * 0.25;
                var expected = new Quaternion(axis, angle);

                var m = Matrix3d.RotationX(angle);
                var actual = Quaternion.FromRotationMatrix(m);
                Assert.IsTrue(expected.IsSame(actual, 1.0e-6));
            }

            {
                var axis = new Vector3d(-1, 0, 0);
                var angle = System.Math.PI * 0.5;
                var expected = new Quaternion(axis, angle);

                var m = Matrix3d.RotationX(angle);
                var actual = Quaternion.FromRotationMatrix(m);
                Assert.IsTrue(expected.IsSame(actual, 1.0e-6));
            }

            {
                var axis = new Vector3d(1, 0, 0);
                var angle = System.Math.PI * 0.75;
                var expected = new Quaternion(axis, angle);

                var m = Matrix3d.RotationX(angle);
                var actual = Quaternion.FromRotationMatrix(m);
                Assert.IsTrue(expected.IsSame(actual, 1.0e-3));
            }


            {
                var axis = new Vector3d(0, -1, 0);
                var angle = System.Math.PI * 0.5;
                var expected = new Quaternion(axis, angle);

                var m = Matrix3d.RotationY(angle);
                var actual = Quaternion.FromRotationMatrix(m);
                Assert.IsTrue(expected.IsSame(actual, 1.0e-6));
            }

            {
                var axis = new Vector3d(0, 0, -1);
                var angle = System.Math.PI * 0.5;
                var expected = new Quaternion(axis, angle);

                var m = Matrix3d.RotationZ(angle);
                var actual = Quaternion.FromRotationMatrix(m);
                Assert.IsTrue(expected.IsSame(actual, 1.0e-6));
            }
        }

        [TestMethod]
        public void TestToRotationMatrix()
        {
            {
                var angle = 0.5 * System.Math.PI;
                var q = new Quaternion(new Vector3d(1.0, 0.0, 0.0), angle);
                var actual = q.ToRotationMatrix();
                var expected = Matrix3d.RotationX(angle);
                Assert.IsTrue(expected.IsSame(actual, 1.0e-6));
            }

            {
                var angle = 0.5 * System.Math.PI;
                var q = new Quaternion(new Vector3d(0.0, 1.0, 0.0), angle);
                var actual = q.ToRotationMatrix();
                var expected = Matrix3d.RotationY(angle);
                Assert.IsTrue(expected.IsSame(actual, 1.0e-6));
            }

            {
                var angle = 0.5 * System.Math.PI;
                var q = new Quaternion(new Vector3d(0.0, 0.0, 1.0), angle);
                var actual = q.ToRotationMatrix();
                var expected = Matrix3d.RotationZ(angle);
                Assert.IsTrue(expected.IsSame(actual, 1.0e-6));
            }


        }
    }
}
