using PG.CGStudio;
using PG.CGStudio.UICtrl;
using PG.Core;
using PG.Core.Math;
using System;
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

        private static Canvas3d instance;
        public static Canvas3d Instance
        {
            get { return instance; }
        }

        public CameraModel Camera { get; private set; }

        public Canvas3d()
        {
            this.ctrl = new CGStudio.UICtrl.CameraUICtrl();
            instance = this;
        }

        public void CreateRenderer(System.IntPtr handle, World world)
        {
            renderer = new PG.CLI.Renderer(handle, World.Instance.Adapter);
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
            throw new NotImplementedException();
        }

        public void OnMiddleButtonDragging(Vector2d position)
        {
            throw new NotImplementedException();
        }

        public void OnMiddleButtonUp(Vector2d position)
        {
            throw new NotImplementedException();
        }

        public void OnWheel(double dx)
        {
            throw new NotImplementedException();
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
            Renderer.Render(width, height, World.Instance.Adapter);
        }

        public void Update(World model)
        {
            Renderer.Update(model.Adapter);
        }

        private int width;
        private int height;

        public void ChangeSize(int width, int height)
        {
            this.width = width;
            this.height = height;
        }

        public ObjectId GetObjectId(Vector2d position)
        {
            //var model = MainModel.Instance;
            Renderer.Bind();
            var command = new PG.CLI.Command(PG.PickLabels.PickCommandLabel);
            command.SetArg(PG.PickLabels.PositionLabel, new Vector2d(position.X, 1.0 - position.Y));
            command.Execute(World.Instance.Adapter);
            var parentId = command.GetResult<int>(PG.PickLabels.ParentIdLabel);
            var childId = command.GetResult<int>(PG.PickLabels.ChildIdLabel);
            Renderer.UnBind();
            return new ObjectId(parentId, childId);
        }

        public void BuildShader(World world, int id)
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
