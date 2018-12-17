using PG.Core.Shape;

namespace PG.CGStudio
{
    public class MainModel
    {
        private PG.CLI.Model model;

        static MainModel instance;

        public static MainModel Instance { get { return instance; } }

        public MainModel()
        {
            model = new PG.CLI.Model();
            instance = this;
        }

        public int Add(ParticleSystem particleSystem)
        {
            return model.AddParticleSystem(particleSystem);
        }

        public int Add(WireFrame wireFrame)
        {
            return model.AddWireFrame(wireFrame);
        }

        public int Add(PolygonMesh polygonMesh)
        {
            return model.AddPolygonMesh(polygonMesh);
        }
    }
}
