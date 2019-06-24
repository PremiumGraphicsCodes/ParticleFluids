using PG.CGStudio.Object.PolygonMesh;
using Reactive.Bindings;
using System.Linq;

namespace PG.CGStudio
{
    public class PolygonMeshObjectRepository
    {
        private PG.CLI.PolygonMeshObjectRepositoryAdapter adapter;

        public PG.CLI.PolygonMeshObjectRepositoryAdapter Adapter { get { return adapter; } }

        public ReactiveCollection<PolygonMeshObjectModel> Meshes { get; }

        public PolygonMeshObjectRepository(PG.CLI.PolygonMeshObjectRepositoryAdapter adapter)
        {
            this.adapter = adapter;
            this.Meshes = new ReactiveCollection<PolygonMeshObjectModel>();
        }

        public void Clear()
        {
            Meshes.Clear();
            adapter.Clear();
        }

        public void Sync()
        {
            this.Meshes.Clear();
            var objects = adapter.GetObjects();
            foreach (var o in objects)
            {
                var item = new PolygonMeshObjectModel(o);
                this.Meshes.Add(item);
            }
        }

        public PolygonMeshObjectModel FindObjectById(int id)
        {
            return Meshes.FirstOrDefault(x => x.Id.Value == id);
        }
    }
}
