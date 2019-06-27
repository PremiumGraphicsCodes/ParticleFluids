using PG.Core.Shape;

namespace PG.Scene
{
    public class PolygonMeshScene : ISceneNode
    {
        private PolygonMesh shape;

        public override string Name { get; }

        public PolygonMeshScene()
        {
        }

        public PolygonMeshScene(PolygonMesh shape)
        {
            this.shape = shape;
        }
    }
}
