using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.Math
{
    public class Triangle3d
    {
        private Vector3d v1;
        private Vector3d v2;
        private Vector3d v3;

        public Triangle3d(Vector3d v1, Vector3d v2, Vector3d v3)
        {
            this.v1 = v1;
            this.v2 = v2;
            this.v3 = v3;
        }

        public Vector3d Normal
        {
            get
            {
                var v21 = (v2 - v1).Normalized;
                var v31 = (v3 - v1).Normalized;
                return v21.Cross(v31);
            }
        }
    }
}
