using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Core;

namespace PGCoreTest
{
    [TestClass]
    public class CircularBuffer1dTest
    {
        [TestMethod]
        public void TestGet()
        {
            var buffer = new CircularBuffer1d<int>(10, 0);
            buffer.Set(11, 314);
            Assert.AreEqual(314, buffer.Get(1));
        }

        [TestMethod]
        public void TestIndexer()
        {
            var buffer = new CircularBuffer1d<int>(10, 0);
            buffer[11] = 314;
            Assert.AreEqual(314, buffer[1]);
        }

    }
}
