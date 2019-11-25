using PG.Core.Math;
using PG.Core.Shape;
using PG.Core.UI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.CGStudio.Scene.Shape
{
    public class SelectedShapeSceneModel
    {
        public SelectedShapeSceneModel(int id)
        {
            this.id = id;
            CreateBoundingBoxItem();
            CreateAxes();
        }

        private void CreateBoundingBoxItem()
        {
            var world = MainModel.Instance.World;
            var bb = PG.CLI.Command.Get<Box3d>(world.Adapter, PG.GetLabels.BoundingBoxLabel, id);
            var builder = new WireFrameBuilder();
            builder.Add(bb);
            var appearance = new WireAppearance
            {
                Color = new Core.Graphics.ColorRGBA(1.0f, 0.0f, 0.0f, 0.0f),
                Width = 1.0f
            };
            this.boundingBoxItemId = world.Items.AddWireFrameScene(builder.Build(), "", appearance);
        }

        private void CreateAxes()
        {
            /*
            var world = MainModel.Instance.World;
            var bb = PG.CLI.Command.Get<Box3d>(world.Adapter, PG.GetLabels.BoundingBoxLabel, id);
            var xwire = new Core.Shape.WireFrame()
            world.Items.AddWireFrameScene()
            */

        }

        private int id;
        private int boundingBoxItemId;
        private int xAxisItemId;
        private int yAxisItemId;
        private int zAxisItemId;
        private int uCircleItemId;
        private int vCircleItemId;

    }
}
