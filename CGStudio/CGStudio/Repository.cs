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

        public bool Import(string filename)
        {
            var command = new PG.CLI.Command("Mock");
            command.SetArg("lhs", 1);
            command.SetArg("rhs", 2);
            command.Execute(adapter);
            var result = command.GetResult("value");
            /*
            var isOk = adapter.Import(filename);
            if(isOk)
            {
                Sync();
            }
            return isOk;
            */
            return false;
        }

        public bool Export(string filename)
        {
            return adapter.Export(filename);
        }

        public void AddParticleSystemScene(List<Vector3d> positions, string name)
        {
            this.adapter.GetSceneAdapter().AddParticleSystemScene(positions, name);
            Sync();
        }

        public void AddWireFrameScene(List<Line3d> lines, string name, Core.UI.WireAppearance appearance)
        {
            this.adapter.GetSceneAdapter().AddWireFrameScene(lines, name, appearance);
            Sync();
        }

        public void AddPolygonMeshScene(PolygonMesh polygonMesh, string name)
        {
            this.adapter.GetSceneAdapter().AddPolygonMeshScene(polygonMesh, name);
            Sync();
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

        public void AddParticleSystemItem(List<Vector3d> positions, string name)
        {
            this.adapter.GetItemAdapter().AddParticleSystemScene(positions, name);
            Sync();
        }

        public void AddWireFrameItem(List<Line3d> lines, string name, Core.UI.WireAppearance appearance)
        {
            this.adapter.GetItemAdapter().AddWireFrameScene(lines, name, appearance);
            Sync();
        }

        public void AddPolygonMeshItem(PolygonMesh polygonMesh, string name)
        {
            this.adapter.GetItemAdapter().AddPolygonMeshScene(polygonMesh, name);
            Sync();
        }

        public SceneType GetTypeById(int id)
        {
            var type = (SceneType)this.adapter.GetSceneAdapter().GetTypeById(id);
            return type;
        }
    }
}
