using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.CLI;

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
            command.SetArg("rhs", 1);
            command.SetArg("lhs", 2);
            command.Execute(world);
            var actual = command.GetResult<int>("value");
            Assert.AreEqual(3, actual);
        }
    }
}