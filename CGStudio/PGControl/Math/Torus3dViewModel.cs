using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.Control.Math
{
    public class Torus3dViewModel
    {
        public Vector3dViewModel BottomViewModel { get; }
            = new Vector3dViewModel();

        public ReactiveProperty<double> BigRadius { get; }
            = new ReactiveProperty<double>(10.0);

        public ReactiveProperty<double> SmallRadius { get; }
            = new ReactiveProperty<double>(1.0);

        public Torus3dViewModel()
        { }
    }
}
