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
            = new Vector3dViewModel();

        public Vector3dViewModel UVecViewModel { get; }
            = new Vector3dViewModel();

        public Vector3dViewModel VVecViewModel { get; }
            = new Vector3dViewModel();

        public Circle3d Value
        {
            get        
            {
                return new Circle3d(CenterViewModel.Value, UVecViewModel.Value, VVecViewModel.Value);
            }
        }
    }
}
