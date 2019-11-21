using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.CLI;

namespace PGCommandTest
{
    [TestClass]
    public class CreateSceneTest
    {
        [TestMethod]
        public void TestCreateParticleSystemScene()
        {
            var world = new WorldAdapter();
            var id = CreateParticleSystemScene(world);
            var type = PG.CLI.Command.Get<PG.Core.SceneType>(world, "SceneType", id);
            Assert.AreEqual(PG.Core.SceneType.ParticleSystem, type);
        }

        [TestMethod]
        public void TestCreateWireFrameScene()
        {
            var world = new WorldAdapter();
            var id = CreateWireFrameScene(world);
            var type = PG.CLI.Command.Get<PG.Core.SceneType>(world, "SceneType", id);
            Assert.AreEqual(PG.Core.SceneType.WireFrame, type);
        }

        private int CreateParticleSystemScene(WorldAdapter world)
        {
            var command = new Command(PG.ParticleSystemCreateLabels.ParticleSystemAddLabel);
            command.Execute(world);
            return command.GetResult<int>(PG.ParticleSystemCreateLabels.NewIdLabel);
        }

        private int CreateWireFrameScene(WorldAdapter world)
        {
            var command = new Command(PG.WireFrameCreateLabels.WireFrameAddLabel);
            command.Execute(world);
            return command.GetResult<int>(PG.WireFrameCreateLabels.NewIdLabel);
        }

        /*
        private int CreatePolygonMeshScene(WorldAdapter world)
        {
            var command = new Command(PG.PolygonMeshAddLabels.);
            command.Execute(world);
            return command.GetResult<int>(PG.PolygonMeshAddLabels.NewIdLabel);
        }
        */
    }
}
