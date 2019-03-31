using PG.Core.Shape;
using PG.Core.UI;

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

        public int Add(ParticleSystem particleSystem, ParticleAppearance appearance)
        {
            return adapter.AddParticleSystem(particleSystem, appearance);
        }

        public int Add(WireFrame wireFrame, WireAppearance appearance)
        {
            return adapter.AddWireFrame(wireFrame, appearance);
        }

        public int Add(PolygonMesh polygonMesh)
        {
            return adapter.AddPolygonMesh(polygonMesh);
        }
    }
}
