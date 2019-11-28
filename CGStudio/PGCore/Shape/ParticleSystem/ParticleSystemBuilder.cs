using System.Collections.Generic;
using PG.Core.Math;

namespace PG.Core.Shape
{
    public class ParticleSystemBuilder
    {
        private readonly List<Vector3d> positions = new List<Vector3d>();

        public ParticleSystemBuilder()
        {
        }

        public void Add(ICurve3d curve, int udiv)
        {
            for (int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                positions.Add(curve.GetPosition(u));
            }
        }

        public void Add(ISurface3d surface, int udiv, int vdiv)
        {
            for (int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                for (int j = 0; j < vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    positions.Add(surface.GetPosition(u, v));
                }
            }
        }

        public void Add(IVolume3d volume, int udiv, int vdiv)
        {
            for (int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                for (int j = 0; j < vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    positions.Add(volume.GetPosition(1.0, u, v));
                }
            }
            for (int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                for (int j = 0; j < vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    positions.Add(volume.GetPosition(-1.0, u, v));
                }
            }
            for (int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                for (int j = 0; j < vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    positions.Add(volume.GetPosition(u, 1.0, v));
                }
            }
            for (int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                for (int j = 0; j < vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    positions.Add(volume.GetPosition(u, -1.0, v));
                }
            }
            for (int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                for (int j = 0; j < vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    positions.Add(volume.GetPosition(u, v, -1.0));
                }
            }
            for (int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                for (int j = 0; j < vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    positions.Add(volume.GetPosition(u, v, 1.0));
                }
            }
        }

        public ParticleSystem ToParticleSystem()
        {
            return new ParticleSystem(positions);
        }
    }
}
