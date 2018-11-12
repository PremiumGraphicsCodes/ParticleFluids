using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Math;

namespace PGCoreTest.Math
{
    [TestClass]
    public class Line3dTest
    {
        [TestMethod]
        public void TestLength()
        {
            var l = new Line3d(new Vector3d(0, 0, 0), new Vector3d(10, 0, 0));
        }

    }
}
