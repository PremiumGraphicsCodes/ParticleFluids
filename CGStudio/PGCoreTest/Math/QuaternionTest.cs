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
            var axis = new Vector3d(1,0,0);
            var angle = System.Math.PI / 0.5;
            var expected = new Quaternion(axis, angle);
            var m = Matrix3d.RotationX(angle);

            var q = new Quaternion();
            q.FromRotationMatrix(m);
            Assert.IsTrue(expected.IsSame(q, 1.0e-6));
        }

        /*
        [TestMethod]
        public void TestToRotationMatrix()
        {
            var q = new Quaternion(1.0, 0.0, 0.0, 0.0);
            var m = q.ToRotationMatrix();

            var expected = Matrix3d.RotationX(0.5 * System.Math.PI);
        }
        */
    }
}
