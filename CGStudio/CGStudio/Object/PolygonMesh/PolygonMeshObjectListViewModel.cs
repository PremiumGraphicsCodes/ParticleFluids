using Reactive.Bindings;

namespace PG.CGStudio.Object.PolygonMesh
{
    public class PolygonMeshObjectListViewModel
    {
        public ReadOnlyReactiveCollection<PolygonMeshObjectModel> Items { get; }

        public PolygonMeshObjectListViewModel()
        {
            Items = MainModel.Instance.Repository.Objects.PolygonMeshes.Meshes.ToReadOnlyReactiveCollection();
        }
    }
}
