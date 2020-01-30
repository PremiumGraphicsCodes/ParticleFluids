using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Control;

namespace PGControlTest
{
    [TestClass]
    public class CameraModelTest
    {
        [TestMethod]
        public void TestSetXY()
        {
            var adapter = new PG.CLI.WorldAdapter();
            var camera = new CameraModel(adapter);
            camera.SetXY();
        }

        [TestMethod]
        public void TestSetYZ()
        {
            var adapter = new PG.CLI.WorldAdapter();
            var camera = new CameraModel(adapter);
            camera.SetYZ();
        }

        [TestMethod]
        public void TestSetZX()
        {
            var adapter = new PG.CLI.WorldAdapter();
            var camera = new CameraModel(adapter);
            camera.SetZX();
        }

        [TestMethod]
        public void TestFit()
        {
            var adapter = new PG.CLI.WorldAdapter();
            var camera = new CameraModel(adapter);
            camera.Fit();
        }
    }
}
