using PG.Control.Math;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.CGStudio.Generation.WireFrame
{
    public class CircleGenerationViewModel : BindableBase
    {
        public Circle3dViewModel Circle { get; }
            = new Circle3dViewModel();
    }
}
