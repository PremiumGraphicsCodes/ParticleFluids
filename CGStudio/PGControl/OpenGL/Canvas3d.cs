using PG.CGStudio;
using PG.CGStudio.UICtrl;
using PG.Core;
using PG.Core.Math;
using PG.Scene;
using System;
using System.Drawing;
using System.Windows.Input;

namespace PG.Control.OpenGL
{
    public class Canvas3d : IUICtrl
    {
        private CGStudio.UICtrl.IUICtrl ctrl;
        public CGStudio.UICtrl.IUICtrl UICtrl
        {
            get { return ctrl; }
            set { this.ctrl = value; }
        }

        private PG.CLI.Renderer renderer;
        public PG.CLI.Renderer Renderer { get { return renderer; } }

        private readonly SceneList world;

        public CameraModel Camera { get; private set; }

        public Canvas3d(SceneList world)
        {
            this.world = world;
            this.ctrl = new CGStudio.UICtrl.CameraUICtrl(world, this);
        }

        public void CreateRenderer(System.IntPtr handle)
        {
            renderer = new PG.CLI.Renderer(handle, world.Adapter);
            this.renderer.Build(world.Adapter);
            this.Camera = new CameraModel(world.Adapter);
        }

        public void OnLeftButtonDown(Vector2d position)
        {
            this.ctrl.OnLeftButtonDown(position);
        }

        public void OnLeftButtonDragging(Vector2d position)
        {
            this.ctrl.OnLeftButtonDragging(position);
        }

        public void OnLeftButtonUp(Vector2d position)
        {
            this.ctrl.OnLeftButtonUp(position);
        }

        public void OnRightButtonDown(Vector2d position)
        {
            this.ctrl.OnRightButtonDown(position);
        }

        public void OnRightButtonDragging(Vector2d position)
        {
            this.ctrl.OnRightButtonDragging(position);
        }

        public void OnRightButtonUp(Vector2d position)
        {
            this.ctrl.OnRightButtonUp(position);
        }

        public void OnMiddleButtonDown(Vector2d position)
        {
            this.ctrl.OnMiddleButtonDown(position);
        }

        public void OnMiddleButtonDragging(Vector2d position)
        {
            this.ctrl.OnMiddleButtonDragging(position);
        }

        public void OnMiddleButtonUp(Vector2d position)
        {
            this.ctrl.OnMiddleButtonUp(position);
        }

        public void OnWheel(double dx)
        {
            this.ctrl.OnWheel(dx);
        }

        public void OnKeyDown(Key key)
        {
            this.ctrl.OnKeyDown(key);
        }

        public void OnKeyUp(Key key)
        {
            this.UICtrl.OnKeyUp(key);
        }

        public void Render()
        {
            Renderer.Render(width, height, world.Adapter);
        }

        public void Update()
        {
            Renderer.Update(world.Adapter);
        }

        private int width;
        private int height;

        public void ChangeSize(int width, int height)
        {
            this.width = width;
            this.height = height;
        }

        public SceneId GetObjectId(int x, int y)
        {
            var xx = x / (double)width;
            var yy = y / (double)height;
            return GetObjectId(x, y);
        }

        public Point ToScreenCoord(Vector2d position)
        {
            var x = (int)(position.X * width);
            var y = (int)(position.Y * height);
            return new Point(x, y);
        }

        public Vector2d FromScreenCoord(Point point)
        {
            var xx = (double)(point.X / width);
            var yy = (double)(point.Y / height);
            return new Vector2d(xx, yy);
        }

        public SceneId GetObjectId(Vector2d position)
        {
            //var model = MainModel.Instance;
            Renderer.Bind();
            var command = new PG.CLI.Command(PG.PickLabels.PickCommandLabel);
            command.SetArg(PG.PickLabels.PositionLabel, new Vector2d(position.X, 1.0 - position.Y));
            command.Execute(world.Adapter);
            var parentId = command.GetResult<int>(PG.PickLabels.ParentIdLabel);
            var childId = command.GetResult<int>(PG.PickLabels.ChildIdLabel);
            Renderer.UnBind();
            return new SceneId(parentId, childId);
        }

        public void BuildShader(SceneList world, int id)
        {
            var command = new PG.CLI.Command();
            command.Create(PG.ShaderBuildLabels.CommandNameLabel);
            command.SetArg(PG.ShaderBuildLabels.IdLabel, id);

            Renderer.Bind();
            command.Execute(world.Adapter);
            Renderer.UnBind();
        }

    }

}
