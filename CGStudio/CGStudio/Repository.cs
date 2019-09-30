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
        private PG.CLI.RepositoryAdapter adapter;
        public PG.CLI.RepositoryAdapter Adapter { get { return adapter; } }

        public ReactiveCollection<PG.Core.Scene> Scene;

        public Repository()
        {
            this.adapter = new PG.CLI.RepositoryAdapter();
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
            var isOk = (bool)command.GetResult("IsOk");
            return isOk;
        }

        public bool Export(string filePath)
        {
            var command = new PG.CLI.Command("FileExport");
            command.SetArg("FilePath", filePath);
            command.Execute(adapter);
            var isOk = (bool)command.GetResult("IsOk");
            return false;
        }

        public int AddParticleSystemScene(List<Vector3d> positions, string name)
        {
            var command = new PG.CLI.Command("ParticleSystemAdd");
            command.SetArg("Positions", positions);
            command.SetArg("Name", name);
            command.Execute(adapter);
            var newId = (int)command.GetResult("NewId");
            Sync();
            return newId;
        }

        public int AddWireFrameScene(List<Line3d> lines, string name, Core.UI.WireAppearance appearance)
        {
            var command = new PG.CLI.Command("WireFrameAdd");
            command.SetArg("Lines", lines);
            command.SetArg("Name", name);
            command.Execute(adapter);
            var newId = (int)command.GetResult("NewId");
            Sync();
            return newId;
        }

        public int AddPolygonMeshScene(PolygonMesh polygonMesh, string name)
        {
            var command = new PG.CLI.Command("PolygonMeshAdd");
//            command.SetArg("Lines", lines);
//            command.SetArg("Name", name);
            command.Execute(adapter);
            var newId = (int)command.GetResult("NewId");
            Sync();
            return newId;
        }

        public void AddMaterialScene(PG.Core.Graphics.Material material, string name)
        {
            this.adapter.GetSceneAdapter().AddMaterialScene(material, name);
            Sync();
        }

        public void AddLightScene(PG.Core.Graphics.PointLight light, string name)
        {
            this.adapter.GetSceneAdapter().AddLightScene(light, name);
            Sync();
        }

        public void ChangeName(int id, string name)
        {
            this.Adapter.GetSceneAdapter().ChangeName(id, name);
            Sync();
        }

        public void UpdateLightScene(int id, PG.Core.Graphics.PointLight light)
        {
            this.adapter.GetSceneAdapter().UpdateLightScene(id, light);
        }

        public void UpdateMaterialScene(int id, PG.Core.Graphics.Material material)
        {
            this.adapter.GetSceneAdapter().UpdateMaterialScene(id, material);
        }

        private void Sync()
        {
            var newScene = this.adapter.GetSceneAdapter().ToScene();
            Scene[0] = newScene;
        }

        public SceneType GetTypeById(int id)
        {
            var type = (SceneType)this.adapter.GetSceneAdapter().GetTypeById(id);
            return type;
        }
    }
}
