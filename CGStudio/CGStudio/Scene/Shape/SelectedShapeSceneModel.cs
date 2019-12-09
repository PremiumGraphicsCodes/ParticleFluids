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
            CreateCircleU(bb);
            CreateCircleV(bb);
        }

        public void ClearItems()
        {
            var world = MainModel.Instance.World;
            world.Scenes.Delete(boundingBoxItemId);
            world.Scenes.Delete(xAxisItemId);
            world.Scenes.Delete(yAxisItemId);
            world.Scenes.Delete(zAxisItemId);
            world.Scenes.Delete(uCircleItemId);
            world.Scenes.Delete(vCircleItemId);
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
            this.boundingBoxItemId = world.Scenes.AddWireFrameScene(builder.ToWireFrame(), "", appearance, 0);
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
            this.xAxisItemId = world.Scenes.AddWireFrameScene(builder.ToWireFrame(), "", appearance, 0);
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
            this.yAxisItemId = world.Scenes.AddWireFrameScene(builder.ToWireFrame(), "", appearance, 0);
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
            this.zAxisItemId = world.Scenes.AddWireFrameScene(builder.ToWireFrame(), "", appearance, 0);
        }

        private void CreateCircleU(Box3d bb)
        {
            var world = MainModel.Instance.World;
            var length = bb.Length.Max();
            var circle = new Ellipse3d(bb.GetPosition(0.5, 0.5, 0.5), new Vector3d(length, 0.0, 0.0), new Vector3d(0.0, length, 0.0));
            var builder = new WireFrameBuilder();
            builder.Add(circle, 36);
            var appearance = new WireAppearance
            {
                Color = new Core.Graphics.ColorRGBA(1.0f, 1.0f, 0.0f, 0.0f),
                Width = 1.0f
            };
            this.uCircleItemId = world.Scenes.AddWireFrameScene(builder.ToWireFrame(), "", appearance, 0);
        }

        private void CreateCircleV(Box3d bb)
        {
            var world = MainModel.Instance.World;
            var length = bb.Length.Max();
            var circle = new Ellipse3d(bb.GetPosition(0.5, 0.5, 0.5), new Vector3d(length, 0.0, 0.0), new Vector3d(0.0, 0.0, length));
            var builder = new WireFrameBuilder();
            builder.Add(circle, 36);
            var appearance = new WireAppearance
            {
                Color = new Core.Graphics.ColorRGBA(1.0f, 0.0f, 1.0f, 0.0f),
                Width = 1.0f
            };
            this.vCircleItemId = world.Scenes.AddWireFrameScene(builder.ToWireFrame(), "", appearance, 0);
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
