﻿using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.CLI;

namespace PGCommandTest
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestGetSceneType()
        {
            var world = new WorldAdapter();
            var id = CreateParticleSystemScene(world);
            var type = PG.CLI.Command.Get<PG.Core.SceneType>(world, "SceneType", id);
            Assert.AreEqual(PG.Core.SceneType.ParticleSystem, type);

            id = CreateWireFrameScene(world);
            type = PG.CLI.Command.Get<PG.Core.SceneType>(world, "SceneType", id);
            Assert.AreEqual(PG.Core.SceneType.WireFrame, type);
        }

        private int CreateParticleSystemScene(WorldAdapter world)
        {
            var command = new Command(PG.ParticleSystemAddLabels.ParticleSystemAddLabel);
            command.Execute(world);
            return command.GetResult<int>(PG.ParticleSystemAddLabels.NewIdLabel);
        }

        private int CreateWireFrameScene(WorldAdapter world)
        {
            var command = new Command(PG.WireFrameAddLabels.WireFrameAddLabel);
            command.Execute(world);
            return command.GetResult<int>(PG.WireFrameAddLabels.NewIdLabel);
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
