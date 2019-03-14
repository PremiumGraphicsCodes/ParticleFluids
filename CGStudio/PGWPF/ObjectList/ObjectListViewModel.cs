using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.CGStudio
{
    public class Object
    {
        public string Name { get; set; }
    }
    
    public class ObjectListViewModel
    {
        public List<Object> Objects { get; set; }

        public ObjectListViewModel()
        {
            Objects = new List<Object>();
        }
    }
}
