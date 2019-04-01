using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.CGStudio.Material
{
    public class MaterialObjectRepository
    {
        private PG.CLI.MaterialObjectRepositoryAdapter adapter;

        public MaterialObjectRepository()
        {
            this.adapter = new PG.CLI.MaterialObjectRepositoryAdapter();
        }

        public int Add(PG.Core.Graphics.Material material)
        {
            return this.adapter.Add(material);
        }
    }
}
