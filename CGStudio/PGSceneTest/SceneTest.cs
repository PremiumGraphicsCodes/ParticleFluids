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
            var scene = new Scene(1, "Root", SceneType.Root);
        }
    }
}
