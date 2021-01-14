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

        public bool DoConvertToVolume { get; set; }

        public double Radius { get; set; } = 5.0;

        public void ExportFiles(SceneList world, FluidScene fluid, VDBModel vdb, int timeStep)
        {
            if(DoExportVDB)
            {
                var filePath = VDBExportDirectory + "/" + fluid.Name + "_" + timeStep.ToString() + ".vdb";
                var ids = new List<int>();
                ids.Add(fluid.Id);
                vdb.Write(filePath, world, ids);
            }
            /*
            if(DoConvertToVolume)
            {
                var filePath = OBJExportDirectory + "/" + fluid.Name + "_" + timeStep.ToString() + ".obj";
                vdb.WriteOBJ(world, fluid.PolygonMeshId, filePath);
            }
            */
        }
    }
}
