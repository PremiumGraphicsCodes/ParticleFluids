using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using PG.Core.Math;

namespace PGCoreTest.Math
{
    [TestClass]
    public class Box3dTest
    {
        private double tolerance = 1.0e-9;

        [TestMethod]
        public void TestVolume()
        {
            {
                var box = new Box3d();
                Assert.AreEqual(1.0, box.Volume, tolerance);
            }

            {
                var v1 = new Vector3d(0, 0, 0);
                var v2 = new Vector3d(10, 1, 1);
                var box = new Box3d(v1,v2);
                Assert.AreEqual(10.0, box.Volume, tolerance);
            }
        }
    }
}
