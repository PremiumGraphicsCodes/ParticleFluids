using PG.Core.Math;
using PG.Core.Shape;
using PG.Core.UI;

namespace PG.CGStudio.Scene.Shape
{
    public class SelectedShapeSceneModel
    {
        public SelectedShapeSceneModel(int id)
        {
            this.id = id;
            var world = MainModel.Instance.World;
            var bb = PG.CLI.Command.Get<Box3d>(world.Adapter, PG.GetLabels.BoundingBoxLabel, id);
            CreateBoundingBoxItem(bb);
            CreateAxesX(bb);
            CreateAxesY(bb);
            CreateAxesZ(bb);
        }

        public void ClearItems()
        {
            var world = MainModel.Instance.World;
            world.Items.Delete(boundingBoxItemId);
            world.Items.Delete(xAxisItemId);
            world.Items.Delete(yAxisItemId);
            world.Items.Delete(zAxisItemId);
        }

        public int Id { get { return id; } }

        private void CreateBoundingBoxItem(Box3d bb)
        {
            var world = MainModel.Instance.World;
            var builder = new WireFrameBuilder();
            builder.Add(bb);
            var appearance = new WireAppearance
            {
                Color = new Core.Graphics.ColorRGBA(1.0f, 0.0f, 0.0f, 0.0f),
                Width = 1.0f
            };
            this.boundingBoxItemId = world.Items.AddWireFrameScene(builder.Build(), "", appearance);
        }

        private void CreateAxesX(Box3d bb)
        {
            var world = MainModel.Instance.World;
            var xline = new Line3d(bb.GetPosition(0.5, 0.5, 0.5), bb.GetPosition(1.5, 0.5, 0.5));
            var builder = new WireFrameBuilder();
            builder.Add(xline);
            var appearance = new WireAppearance
            {
                Color = new Core.Graphics.ColorRGBA(1.0f, 0.0f, 0.0f, 0.0f),
                Width = 1.0f
            };
            this.xAxisItemId = world.Items.AddWireFrameScene(builder.Build(), "", appearance);
        }

        private void CreateAxesY(Box3d bb)
        {
            var world = MainModel.Instance.World;
            var xline = new Line3d(bb.GetPosition(0.5, 0.5, 0.5), bb.GetPosition(0.5, 1.5, 0.5));
            var builder = new WireFrameBuilder();
            builder.Add(xline);
            var appearance = new WireAppearance
            {
                Color = new Core.Graphics.ColorRGBA(0.0f, 1.0f, 0.0f, 0.0f),
                Width = 1.0f
            };
            this.yAxisItemId = world.Items.AddWireFrameScene(builder.Build(), "", appearance);
        }

        private void CreateAxesZ(Box3d bb)
        {
            var world = MainModel.Instance.World;
            var xline = new Line3d(bb.GetPosition(0.5, 0.5, 0.5), bb.GetPosition(0.5, 0.5, 1.5));
            var builder = new WireFrameBuilder();
            builder.Add(xline);
            var appearance = new WireAppearance
            {
                Color = new Core.Graphics.ColorRGBA(0.0f, 0.0f, 1.0f, 0.0f),
                Width = 1.0f
            };
            this.zAxisItemId = world.Items.AddWireFrameScene(builder.Build(), "", appearance);

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
