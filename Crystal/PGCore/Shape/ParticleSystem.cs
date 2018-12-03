using System.Collections.Generic;
using PG.Core.Math;

namespace PG.Core.Shape
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
