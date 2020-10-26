using FluidStudio.VDB;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio
{
    public class MainModel
    {
        public VDBModel VDBModel { get; }
        
        public MainModel()
        {
            this.VDBModel = new VDBModel();
        }
    }
}
