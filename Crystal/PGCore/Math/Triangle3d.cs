using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.Math
{
    public class Triangle3d
    {
        public Vector3d v1;
        public Vector3d v2;
        public Vector3d v3;

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
