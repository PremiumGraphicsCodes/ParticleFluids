using PG.Core.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.Control.Math
{
    public class Quad3dViewModel
    {
        public Vector3dViewModel OriginViewModel { get; }
            = new Vector3dViewModel();

        public Vector3dViewModel UVecViewModel { get; }
            = new Vector3dViewModel();

        public Vector3dViewModel VVecViewModel { get; }
            = new Vector3dViewModel();

        public Quad3d Value
        {
            get
            {
                var o = OriginViewModel.Value;
                var u = UVecViewModel.Value;
                var v = VVecViewModel.Value;
                return new Quad3d(o, u, v);
            }
            set
            {
                OriginViewModel.Value = value.Origin;
                UVecViewModel.Value = value.UVec;
                VVecViewModel.Value = value.VVec;
            }
        }

        public Quad3dViewModel()
        {
            OriginViewModel.Value = new Core.Math.Vector3d(0, 0, 0);
            UVecViewModel.Value = new Core.Math.Vector3d(1, 0, 0);
            VVecViewModel.Value = new Core.Math.Vector3d(0, 1, 0);
        }
    }
}
