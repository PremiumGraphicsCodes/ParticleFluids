using PG.CLI;

namespace PG.CGStudio.Object.PolygonMesh
{
    public class PolygonMeshObjectModel : ObjectModel
    {
        private PolygonMeshObjectAdapter adapter { get; }

        public PolygonMeshObjectModel(PolygonMeshObjectAdapter adapter) :
            base(adapter)
        {
            this.adapter = adapter;
        }

        public int GetAttributeByFaceId(int faceId)
        {
            return adapter.GetAttributeIdById(faceId);
        }
    }
}
