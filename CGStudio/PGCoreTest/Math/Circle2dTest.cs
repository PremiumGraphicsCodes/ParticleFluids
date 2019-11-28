using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core.Math;

namespace PGCoreTest.Math
{
    [TestClass]
    public class Circle2dTest
    {
        [TestMethod]
        public void TestGetposition()
        {
            var circle = new Circle2d(1.0, new Vector2d(0,0));
            var expected = new Vector2d(1.0, 0.0);
            var actual = circle.GetPosition(0);
            Assert.IsTrue(expected.IsSame(actual, 1.0e-12));
        }
    }
}
