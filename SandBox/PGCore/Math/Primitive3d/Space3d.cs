using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.Core.Math
{
    public class Space3d
    {
        public void Add(IVolume3d volume)
        {
            this.volumes.Add(volume);
        }

        public bool IsInside(Vector3d position)
        {
            foreach(var v in volumes)
            {
                if(!v.IsInside(position))
                {
                    return false;
                }
            }
            return true;
        }

        public IEnumerable<IVolume3d> Volumes { get { return volumes; } }

        private readonly List<IVolume3d> volumes = new List<IVolume3d>();
    }
}
