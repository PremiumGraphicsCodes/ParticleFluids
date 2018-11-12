using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Math;

namespace PGCoreTest
{
    [TestClass]
    public class Vector3dTest
    {
        [TestMethod]
        public void TestLengthSquard()
        {
            var vector = new Vector3d(10.0, 0.0, 0.0);
            Assert.AreEqual( vector.LengthSquared, 100.0 );
        }

        [TestMethod]
        public void TestLength()
        {
            var vector = new Vector3d(10.0, 0.0, 0.0);
            Assert.AreEqual(vector.Length, 10.0);
        }
    }
}
