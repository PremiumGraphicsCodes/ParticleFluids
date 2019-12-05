using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;

namespace PGCoreTest
{
    [TestClass]
    public class Quad3dTest
    {
        private readonly double tolerance = 1.0e-12;

        [TestMethod]
        public void TestGetPosition()
        {
            var quad = new Quad3d(new Vector3d(0,0,0), new Vector3d(10,0,0), new Vector3d(0,10,0));

            {
                var actual = quad.GetPosition(0.5, 0.0);
                var expected = new Vector3d(5.0, 0.0, 0.0);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }

            {
                var actual = quad.GetPosition(0.5, 0.5);
                var expected = new Vector3d(5.0, 5.0, 0.0);
                Assert.IsTrue(expected.IsSame(actual, tolerance));
            }
        }
    }
}
