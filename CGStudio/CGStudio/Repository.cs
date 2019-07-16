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
            var isOk = adapter.Import(filename);
            if(isOk)
            {
                Sync();
            }
            return isOk;
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

        public void AddWireFrameScene(List<Line3d> lines, string name)
        {
            this.adapter.GetSceneAdapter().AddWireFrameScene(lines, name);
            Sync();
        }

        public void AddPolygonMeshScene(PG.Core.Shape.PolygonMesh polygonMesh, string name)
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
    }
}
