using PG.Core.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.Control.Math
{
    public class Circle3dViewModel
    {
        public Vector3dViewModel CenterViewModel { get; }
            = new Vector3dViewModel(new Vector3d(0,0,0));

        public Vector3dViewModel UVecViewModel { get; }
            = new Vector3dViewModel(new Vector3d(1,0,0));

        public Vector3dViewModel VVecViewModel { get; }
            = new Vector3dViewModel(new Vector3d(0,1,0));

        public Ellipse3d Value
        {
            get        
            {
                return new Ellipse3d(CenterViewModel.Value, UVecViewModel.Value, VVecViewModel.Value);
            }
        }
    }
}
