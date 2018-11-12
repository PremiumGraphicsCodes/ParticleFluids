using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PG.Shape;

namespace PG.CGStudio
{
    public class MainModel
    {
        private List<ParticleSystem> particleSystems;
        private List<WireFrame> wireFrames;
        private List<PolygonMesh> polygonMeshes;

        public MainModel()
        {
            this.particleSystems = new List<ParticleSystem>();
            this.wireFrames = new List<WireFrame>();
            this.polygonMeshes = new List<PolygonMesh>();
        }
    }
}
