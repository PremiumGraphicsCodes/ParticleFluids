using FluidStudio.VDB;
using System.Collections.Generic;

namespace FluidStudio.Physics.Fluid
{
    public class FluidFileExportModel
    {
        public bool DoExportVDB { get; set; }

        public string VDBExportDirectory { get; set; }

        public void ExportFiles(string name, int psId, VDBModel vdb, int timeStep)
        {
            if(DoExportVDB)
            {
                var filePath = VDBExportDirectory + "/" + name + "_" + timeStep.ToString() + ".vdb";

                var psIds = new List<int>();
                var volumeIds = new List<int>();
                psIds.Add(psId);
                vdb.Write(filePath, psIds, volumeIds);
            }
        }
    }
}
