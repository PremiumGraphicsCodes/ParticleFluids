using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PG.CLI;
using PG.Core.Math;
using PG.Core.Shape;
using PG.Scene;

namespace PGControlTest
{
    [TestClass]
    public class SceneListModelTest
    {
        [TestMethod]
        public void TestAddParticleSystemScene()
        {
            var adapter = new WorldAdapter();
            var scene = new SceneListModel(adapter);
            var positions = new List<Vector3d>();
            positions.Add(new Vector3d(0, 0, 0));
            var appearance = new PG.Core.UI.ParticleAppearance();
            var id = scene.AddParticleSystemScene(positions, "PS", appearance, 1);
            Assert.AreEqual(1, id);
        }

        [TestMethod]
        public void TestAddWireFrameScene()
        {
            var adapter = new WorldAdapter();
            var scene = new SceneListModel(adapter);
            var builder = new WireFrameBuilder();
            builder.Add(new Line3d(new Vector3d(0,0,0), new Vector3d(1,0,0)));
            var wireFrame = builder.ToWireFrame();
            var appearance = new PG.Core.UI.WireAppearance();
            var id = scene.AddWireFrameScene(wireFrame, "WF", appearance, 1);
            Assert.AreEqual(1, id);
        }

        [TestMethod]
        public void TestAddPolygonMeshScene()
        {
            var adapter = new WorldAdapter();
            var scene = new SceneListModel(adapter);
            var builder = new PolygonMeshBuilder();
            builder.Add(new Box3d(new Vector3d(0, 0, 0), new Vector3d(1, 1, 1)));
            var polygonMesh = builder.ToPolygonMesh();
            var id = scene.AddPolygonMeshScene(polygonMesh, "PM", 1);
            Assert.AreEqual(1, id);
        }

        [TestMethod]
        public void TestAddTextureScene()
        {
            var adapter = new WorldAdapter();
            var scene = new SceneListModel(adapter);
            var id = scene.AddTextureScene("TestTexture.bmp", "Texture");
            Assert.AreEqual(1, id);
        }
    }
}
