using PG.Core.Math;
using System.Collections.Generic;

namespace PG.CGStudio.Scene.Item
{
    public class ItemListModel
    {
        private PG.CLI.WorldAdapter adapter;

        public ItemListModel(PG.CLI.WorldAdapter adapter)
        {
            this.adapter = adapter;
        }

        public int AddParticleSystemScene(List<Vector3d> positions, string name, Core.UI.ParticleAppearance appearance)
        {
            var command = new PG.CLI.Command(PG.ParticleSystemAddLabels.ParticleSystemAddLabel);
            command.SetArg(PG.ParticleSystemAddLabels.PositionsLabel, positions);
            command.SetArg(PG.ParticleSystemAddLabels.NameLabel, name);
            command.SetArg(PG.ParticleSystemAddLabels.PointSizeLabel, appearance.Size);
            command.SetArg(PG.ParticleSystemAddLabels.ColorLabel, appearance.Color);
            command.SetArg(PG.ParticleSystemAddLabels.IsItemLabel, true);
            command.Execute(adapter);
            var newId = command.GetResult<int>(PG.ParticleSystemAddLabels.NewIdLabel);
            return newId;
        }

        public int AddWireFrameScene(List<Line3d> lines, string name, Core.UI.WireAppearance appearance)
        {
            var command = new PG.CLI.Command(PG.WireFrameAddLabels.WireFrameAddLabel);
            command.SetArg(PG.WireFrameAddLabels.LinesLabel, lines);
            command.SetArg(PG.WireFrameAddLabels.NameLabel, name);
            command.SetArg(PG.WireFrameAddLabels.ColorLabel, appearance.Color);
            command.SetArg(PG.WireFrameAddLabels.LineWidthLabel, appearance.Width);
            command.SetArg(PG.WireFrameAddLabels.IsItemLabel, true);
            command.Execute(adapter);
            var newId = command.GetResult<int>(PG.WireFrameAddLabels.NewIdLabel);
            return newId;
        }


    }
}
