using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.CLI;
using PG.Core.Math;

namespace PGCLITest
{
    [TestClass]
    public class CommandTest
    {
        [TestMethod]
        public void TestMock()
        {
            var world = new WorldAdapter();
            var command = new Command("Mock");
            command.Execute(world);
        }
    }
}