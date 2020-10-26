﻿using PG.Scene;
using System.Collections.Generic;
using Labels = PG.VDBFileReadLabels;

namespace FluidStudio.VDB
{
    public class VDBModel
    {
        private readonly SceneList world;
        public VDBModel(SceneList world)
        {
            this.world = world;
        }

        public void Init()
        {
            var command = new PG.CLI.OpenVDBCommand("VDBInit");
            command.Execute(world.Adapter);
        }

        public bool Read(string filePath)
        {
            var command = new PG.CLI.OpenVDBCommand(Labels.CommandNameLabel);
            command.SetArg(Labels.FilePathLabel, filePath);
            if (!command.Execute(world.Adapter))
            {
                return false;
            }
            var newIds = command.GetResult<List<int>>(Labels.NewIdLabel);
            return true;
        }
    }
}
