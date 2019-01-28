using PG.Core.Shape;

namespace PG.CGStudio
{
    public class MainModel
    {
        private PG.CLI.ModelAdapter adapter;

        static MainModel instance;

        public static MainModel Instance { get { return instance; } }

        public PG.CLI.ModelAdapter Adapter { get { return adapter; } }

        public MainModel()
        {
            adapter = new PG.CLI.ModelAdapter();
            instance = this;
        }

        public void New()
        {
        }

        public bool Open(string filename)
        {
            return instance.Open(filename);
        }

        public bool Save(string filename)
        {
            return instance.Save(filename);
        }

        public void Import(string filename)
        {

        }

        public void Export(string filename)
        {

        }

        public int Add(ParticleSystem particleSystem)
        {
            return adapter.AddParticleSystem(particleSystem);
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
