using PG.Core.Shape;

namespace PG.CGStudio
{
    public class ObjectRepository
    {
        private PG.CLI.ObjectRepositoryAdapter adapter;

        public PG.CLI.ObjectRepositoryAdapter Adapter { get { return adapter; } }

        public ObjectRepository(PG.CLI.ObjectRepositoryAdapter adapter)
        {
            this.adapter = adapter;
        }

        public int Add(ParticleSystem particleSystem, Core.Graphics.ColorRGBA color, float size)
        {
            return adapter.AddParticleSystem(particleSystem, color, size);
        }

        public int Add(WireFrame wireFrame)
        {
            return adapter.AddWireFrame(wireFrame);
        }

        public int Add(PolygonMesh polygonMesh)
        {
            return adapter.AddPolygonMesh(polygonMesh);
        }
    }
}
