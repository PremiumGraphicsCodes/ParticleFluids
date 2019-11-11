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
            var command = new PG.CLI.Command(PG.WireFrameCreateLabels.WireFrameAddLabel);
            command.SetArg(PG.WireFrameCreateLabels.LinesLabel, lines);
            command.SetArg(PG.WireFrameCreateLabels.NameLabel, name);
            command.SetArg(PG.WireFrameCreateLabels.ColorLabel, appearance.Color);
            command.SetArg(PG.WireFrameCreateLabels.LineWidthLabel, appearance.Width);
            command.SetArg(PG.WireFrameCreateLabels.IsItemLabel, true);
            command.Execute(adapter);
            var newId = command.GetResult<int>(PG.WireFrameCreateLabels.NewIdLabel);
            return newId;
        }

        public void Clear()
        {
            adapter.ClearItems();
        }
    }
}
