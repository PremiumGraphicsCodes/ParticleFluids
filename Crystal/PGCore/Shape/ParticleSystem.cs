using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PG.Math;

namespace PG.Shape
{
    public class ParticleSystem
    {
        private List<Vector3d> positions;

        public List<Vector3d> Positions
        {
            get { return positions; }
        }

        public ParticleSystem(List<Vector3d> positions)
        {
            this.positions = positions;
        }
    }
}
