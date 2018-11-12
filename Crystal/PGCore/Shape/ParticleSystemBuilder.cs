using PG.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.Shape
{
    public class ParticleSystemBuilder
    {
        private List<Vector3d> positions;

        public void Build(Sphere3d sphere, int udiv, int vdiv)
        {
            var pi = System.Math.PI;
            var dtheta = pi * 2.0 / (double)udiv;
            var dphi = pi / (double)vdiv;
            for(double theta = 0.0; theta <= pi * 2.0; theta += dtheta)
            {
                for (double phi = 0.0; phi < pi; phi += dphi)
                {
                    positions.Add( sphere.GetPosition(theta, phi) );
                }
            }
        }
    }
}
