using System;
using System.Windows;
using System.Windows.Forms;
using System.Windows.Controls;
using System.Windows.Forms.Integration;
using HwndExtensions.Host;
using PG.Core.Math;
using PG.Core;
using PG.CGStudio.UICtrl;
using System.Windows.Input;

namespace PG.CGStudio
{
    public class Panel3d : System.Windows.Forms.Panel
    {
        public Panel3d()
        {
        }

        protected override void OnPaintBackground(System.Windows.Forms.PaintEventArgs pevent)
        {
            ;
        }
    }

    public class Canvas3d : IUICtrl
    {
        private UICtrl.IUICtrl ctrl;
        public UICtrl.IUICtrl UICtrl
        {
            get { return ctrl; }
            set { this.ctrl = value; }
        }

        public Canvas3d()
        {
            this.ctrl = new UICtrl.CameraUICtrl();
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
            throw new NotImplementedException();
        }

        public void OnRightButtonDown(Vector2d position)
        {
            throw new NotImplementedException();
        }

        public void OnRightButtonDragging(Vector2d position)
        {
            throw new NotImplementedException();
        }

        public void OnRightButtonUp(Vector2d position)
        {
            throw new NotImplementedException();
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
            throw new NotImplementedException();
        }

        public void OnKeyUp(Key key)
        {
            this.UICtrl.OnKeyUp(key);
        }
    }

    public class HwndHostPresenter3d : HwndHostPresenter
    {
        private System.Windows.Forms.Panel Panel { get; }

        public Canvas3d Canvas { get; }
            = new Canvas3d();

        public HwndHostPresenter3d()
        {
            var host = new WindowsFormsHost();
            Panel = new Panel3d();
            host.Child = Panel;

            host.Initialized += Host_Initialized;

            HwndHost = host;
            RegisterToAppShutdown();

            instance = this;
        }

        private void Host_Initialized(object sender, EventArgs e)
        {
            World.Instance.CreateRenderer(Panel.Handle);
            Panel.Paint += OnPaint;
            Panel.Resize += OnResize;
            Panel.MouseDown += Panel_MouseDown;
            Panel.MouseUp += Panel_MouseUp;
            Panel.MouseMove += Panel_MouseMove;
            Panel.MouseWheel += Panel_MouseWheel;
        }

        private static HwndHostPresenter3d instance;

        public static HwndHostPresenter3d Instance
        {
            get { return instance; }
        }

        public void Render()
        {
            World.Instance.Renderer.Render(Panel.Width, Panel.Height, World.Instance.Adapter);
        }

        public void Update(World model)
        {
            World.Instance.Renderer.Update(model.Adapter);
        }

        public void BuildShader(World world, int id)
        {
            var command = new PG.CLI.Command();
            command.Create(PG.ShaderBuildLabels.CommandNameLabel);
            command.SetArg(PG.ShaderBuildLabels.IdLabel, id);

            World.Instance.Renderer.Bind();
            command.Execute(world.Adapter);
            World.Instance.Renderer.UnBind();
        }

        private void Panel_MouseWheel(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            Canvas.UICtrl.OnWheel(e.Delta / 1200.0f);
        }

        private void Panel_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            var p = PositionInScreen(e.Location);
            if (e.Button == MouseButtons.Left)
            {
                Canvas.UICtrl.OnLeftButtonUp(p);
            }
            else if (e.Button == MouseButtons.Right)
            {
                Canvas.UICtrl.OnRightButtonUp(p);
            }
        }

        private void Panel_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            var p = PositionInScreen(e.Location);
            if (e.Button == MouseButtons.Left)
            {
                Canvas.UICtrl.OnLeftButtonDragging(p);
            }
            else if (e.Button == MouseButtons.Right)
            {
                Canvas.UICtrl.OnRightButtonDragging(p);
            }
        }

        private void Panel_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            var p = PositionInScreen(e.Location);
            if (e.Button == MouseButtons.Left)
            {
                Canvas.UICtrl.OnLeftButtonDown(p);
            }
            else if (e.Button == MouseButtons.Right)
            {
                Canvas.UICtrl.OnRightButtonDown(p);
            }
        }

        private Vector2d PositionInScreen(System.Drawing.Point p)
        {
            var x = p.X / (double)Panel.Width;
            var y = p.Y / (double)Panel.Height;
            return new Vector2d(x, y);
        }

        private void OnResize(object sender, EventArgs e)
        {
            World.Instance.Renderer.Render(Panel.Width, Panel.Height, World.Instance.Adapter);
        }

        private void OnPaint(object sender, PaintEventArgs e)
        {
            World.Instance.Renderer.Render(Panel.Width, Panel.Height, World.Instance.Adapter);
        }

        private void RegisterToAppShutdown()
        {
            System.Windows.Application.Current.Dispatcher.ShutdownStarted += OnShutdownStarted;
        }

        private void OnShutdownStarted(object sender, EventArgs e)
        {
            Dispose();
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                var host = HwndHost;
                if (host != null)
                    host.Dispose();
            }
        }

        public ObjectId GetObjectId(Vector2d position)
        {
            //var model = MainModel.Instance;
            World.Instance.Renderer.Bind();
            var command = new PG.CLI.Command(PG.PickLabels.PickCommandLabel);
            command.SetArg(PG.PickLabels.PositionLabel, new Vector2d(position.X, 1.0 - position.Y));
            command.Execute(World.Instance.Adapter);
            var parentId = command.GetResult<int>(PG.PickLabels.ParentIdLabel);
            var childId = command.GetResult<int>(PG.PickLabels.ChildIdLabel);
            World.Instance.Renderer.UnBind();
            return new ObjectId(parentId, childId);
        }
    }
}
