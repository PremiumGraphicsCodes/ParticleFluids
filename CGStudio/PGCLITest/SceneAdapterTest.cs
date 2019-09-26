using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.CLI;
using PG.Core.Math;

namespace PGCLITest
{
    [TestClass]
    public class SceneAdapterTest
    {
        /*
        [TestMethod]
        public void TestAddParticleSystemScene()
        {
            var repository = new RepositoryAdapter();
            var adapter = repository.GetSceneAdapter();
            //var adapter = new PolygonMeshObjectAdapter();
        }
        */

    }

    [TestClass]
    public class CommandTest
    {
        [TestMethod]
        public void TestMock()
        {
            var command = new Command();
            command.Create("Mock");
            command.Execute();
        }
    }
}