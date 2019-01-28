using System.Collections.Generic;
using PG.Core.Math;

namespace PG.Core.Shape
{
    public class ParticleSystemBuilder
    {
        private List<Vector3d> positions;

        public ParticleSystemBuilder()
        {
            positions = new List<Vector3d>();
        }

        public void Build(Sphere3d sphere, int udiv, int vdiv)
        {
            for (int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                for (int j = 0; j < vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    positions.Add(sphere.GetPosition(u, v));
                }
            }
        }

        public void Build(Cylinder3d cylinder, int udiv, int vdiv)
        {
            for (int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                for (int j = 0; j < vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    positions.Add(cylinder.GetPosition(u,v));
                }
            }
        }

        public void Build(Box3d box, int udiv, int vdiv)
        {
            /*
            for (int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                for (int j = 0; j < vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    positions.Add(box.GetPosition(u, v));
                }
            }
            */
        }

        public ParticleSystem ParticleSystem { get { return new ParticleSystem(positions); } }
    }
}
