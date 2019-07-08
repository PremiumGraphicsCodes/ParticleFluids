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
        [TestMethod]
        public void TestAddParticleSystemScene()
        {
            var repository = new RepositoryAdapter();
            var adapter = repository.GetSceneAdapter();
            adapter.AddParticleSystemScene(new List<Vector3d>());
            var scene = adapter.ToScene();
            //var adapter = new PolygonMeshObjectAdapter();
        }
    }
}
