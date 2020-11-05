using System;
using System.ComponentModel;
using FluidStudio;
using FluidStudio.FileIO;
using FluidStudio.Physics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace FluidStudioTest
{
    [TestClass]
    public class FSProjFileWriterTest
    {
        [TestMethod]
        public void TestWrite()
        {
            var model = new MainModel();
            var scene = new PhysicsScene();
            scene.Fluids.Add(new FluidScene(model.Scenes, 0, 1.0f, 1.0f));
            var writer = new FSProjFileWriter();
            writer.Write(model);
        }
    }
}
