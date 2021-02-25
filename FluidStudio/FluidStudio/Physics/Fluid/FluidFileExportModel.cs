using FluidStudio.VDB;
using PG.Scene;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.Physics.Fluid
{
    public class FluidFileExportModel
    {
        public bool DoExportVDB { get; set; }

        public string VDBExportDirectory { get; set; }

        public void ExportFiles(SceneList world, FluidScene fluid, VDBModel vdb, int timeStep)
        {
            if(DoExportVDB)
            {
                var filePath = VDBExportDirectory + "/" + fluid.Name + "_" + timeStep.ToString() + ".vdb";

                var psIds = new List<int>();
                var volumeIds = new List<int>();
                psIds.Add(fluid.Id);
                vdb.Write(filePath, psIds, volumeIds);

            }
        }
    }
}
