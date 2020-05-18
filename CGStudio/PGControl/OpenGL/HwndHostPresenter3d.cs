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
using PG.Control.OpenGL;

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
            Canvas.CreateRenderer(Panel.Handle, World.Instance);
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
            Canvas.Renderer.Render(Panel.Width, Panel.Height, World.Instance.Adapter);
        }

        public void Update(World model)
        {
            Canvas.Renderer.Update(model.Adapter);
        }

        public void BuildShader(World world, int id)
        {
            var command = new PG.CLI.Command();
            command.Create(PG.ShaderBuildLabels.CommandNameLabel);
            command.SetArg(PG.ShaderBuildLabels.IdLabel, id);

            Canvas.Renderer.Bind();
            command.Execute(world.Adapter);
            Canvas.Renderer.UnBind();
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
            Canvas.Renderer.Render(Panel.Width, Panel.Height, World.Instance.Adapter);
        }

        private void OnPaint(object sender, PaintEventArgs e)
        {
            Canvas.Renderer.Render(Panel.Width, Panel.Height, World.Instance.Adapter);
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
            Canvas.Renderer.Bind();
            var command = new PG.CLI.Command(PG.PickLabels.PickCommandLabel);
            command.SetArg(PG.PickLabels.PositionLabel, new Vector2d(position.X, 1.0 - position.Y));
            command.Execute(World.Instance.Adapter);
            var parentId = command.GetResult<int>(PG.PickLabels.ParentIdLabel);
            var childId = command.GetResult<int>(PG.PickLabels.ChildIdLabel);
            Canvas.Renderer.UnBind();
            return new ObjectId(parentId, childId);
        }
    }
}
