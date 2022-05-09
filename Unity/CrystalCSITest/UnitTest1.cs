using Microsoft.VisualStudio.TestTools.UnitTesting;
using CrystalCSI;

namespace CrystalCSITest
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()
        {
            var i = CSI.SampleAPIInt(1);
            var f = CSI.SampleAPIFloat(1.0f);
            var d = CSI.SampleAPIDouble(2.0);

            CSI.CreateCommand("Mock");
        }
    }
}
