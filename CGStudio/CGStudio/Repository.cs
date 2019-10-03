using PG.Core;
using PG.Core.Graphics;
using PG.Core.Math;
using PG.Core.Shape;
using Reactive.Bindings;
using System.Collections.Generic;

namespace PG.CGStudio
{
    public class Repository
    {
        private PG.CLI.WorldAdapter adapter;
        public PG.CLI.WorldAdapter Adapter { get { return adapter; } }

        public ReactiveCollection<PG.Core.Scene> Scene;

        public Repository()
        {
            this.adapter = new PG.CLI.WorldAdapter();
            this.Scene = new ReactiveCollection<Core.Scene>();
            this.Scene.Add( new PG.Core.Scene(0, "Root", Core.SceneType.Root) );
        }

        public void New()
        {
            this.adapter.Clear();
            Sync();
        }

        public bool Open(string filename)
        {
            return false;
        }

        public bool Save(string filename)
        {
            return false;
        }

        public bool Import(string filePath)
        {
            var command = new PG.CLI.Command("FileImport");
            command.SetArg("FilePath", filePath);
            command.Execute(adapter);
            var isOk = command.GetResult<bool>("IsOk");
            return isOk;
        }

        public bool Export(string filePath)
        {
            var command = new PG.CLI.Command("FileExport");
            command.SetArg("FilePath", filePath);
            command.Execute(adapter);
            var isOk = command.GetResult<bool>("IsOk");
            return false;
        }

        public int AddParticleSystemScene(List<Vector3d> positions, string name)
        {
            var command = new PG.CLI.Command("ParticleSystemAdd");
            command.SetArg("Positions", positions);
            command.SetArg("Name", name);
            command.Execute(adapter);
            var newId = command.GetResult<int>("NewId");

            command.Create("CameraFit");
            command.Execute(adapter);
            command.Clear();
            Sync();
            return newId;
        }

        public int AddWireFrameScene(List<Line3d> lines, string name, Core.UI.WireAppearance appearance)
        {
            var command = new PG.CLI.Command("WireFrameAdd");
            command.SetArg("Lines", lines);
            command.SetArg("Name", name);
            command.Execute(adapter);
            var newId = command.GetResult<int>("NewId");
            Sync();
            return newId;
        }

        public int AddPolygonMeshScene(PolygonMesh polygonMesh, string name)
        {
            var command = new PG.CLI.Command("PolygonMeshAdd");
//            command.SetArg("Lines", lines);
//            command.SetArg("Name", name);
            command.Execute(adapter);
            var newId = command.GetResult<int>("NewId");
            Sync();
            return newId;
        }

        public int AddMaterialScene(PG.Core.Graphics.Material material, string name)
        {
            var command = new PG.CLI.Command("MaterialAdd");
            command.Execute(adapter);
            var newId = command.GetResult<int>("NewId");
            Sync();
            return newId;
        }

        public int AddLightScene(PG.Core.Graphics.PointLight light, string name)
        {
            var command = new PG.CLI.Command("LightAdd");
            command.Execute(adapter);
            var newId = command.GetResult<int>("NewId");
            Sync();
            return newId;
        }

        private void Sync()
        {
            var scenes = PG.CLI.Command.Get(adapter, "SceneList") as List<string>;
            var root = new PG.Core.Scene(0, "Root", SceneType.Root);
            foreach(var scene in scenes)
            {
                var s = new PG.Core.Scene(0, scene, SceneType.ParticleSystem);
                root.Children.Add(s);
            }
            Scene[0] = root;

            //var newScene = this.adapter.GetSceneAdapter().ToScene();
        }
        /*

        public SceneType GetTypeById(int id)
        {
            var type = (SceneType)this.adapter.GetSceneAdapter().GetTypeById(id);
            return type;
        }
        */
    }
}
