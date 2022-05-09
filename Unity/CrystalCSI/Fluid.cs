using System;
using System.Collections.Generic;
using System.Text;

namespace CrystalCSI
{
    public class Fluid
    {
        private int id;

        public void Create()
        {
            CSI.CreateCommand(PG.FluidSceneCreateCommand.CommandNameLabel);
            CSI.Execute();
            this.id = CSI.GetResultInt(PG.FluidSceneCreateCommand.NewIdLabel);
            
        }
    }
}
