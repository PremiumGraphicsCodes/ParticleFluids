using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.Scene;

namespace PGSceneTest
{
    [TestClass]
    public class SceneTest
    {
        [TestMethod]
        public void TestAdd()
        {
            var scene = new Scene();
            scene.Root.Children.Add(new ParticleSystemScene());
            scene.Root.Children.Add(new WireFrameScene());
            scene.Root.Children.Add(new PolygonMeshScene());
        }
    }
}
