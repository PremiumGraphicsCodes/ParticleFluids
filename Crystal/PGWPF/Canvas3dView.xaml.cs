using System;
using System.Windows.Controls;
using System.Windows.Forms;
using System.Windows.Interop;
using PG.Core.Math;

namespace PG.CGStudio
{
    public partial class Canvas3dView : System.Windows.Controls.UserControl
    {
        private static Canvas3dView instance;
        private UICtrl.UICtrl ctrl;

        public static Canvas3dView Instance
        {
            get { return instance; }
        }

        public void Render()
        {
            adapter.Render(Panel.Width, Panel.Height);
        }

        public void Update(MainModel model)
        {
            adapter.Update(model.Adapter);
        }

        private PG.CLI.Renderer adapter;

        public PG.CLI.Renderer Adapter { get { return adapter; } }

        public Canvas3dView()
        {
            instance = this;
            InitializeComponent();
        }

        private void WindowsFormsHost_Initialized(object sender, System.EventArgs e)
        {
            this.adapter = new PG.CLI.Renderer(Panel.Handle);
            this.ctrl = new UICtrl.CameraUICtrl(adapter.camera);
            Panel.Paint += OnPaint;
            Panel.Resize += OnResize;
            Panel.MouseDown += Panel_MouseDown;
            Panel.MouseUp += Panel_MouseUp;
            Panel.MouseMove += Panel_MouseMove; 
        }

        private void Panel_MouseUp(object sender, MouseEventArgs e)
        {
            var p = PositionInScreen(e.Location);
            if(e.Button == MouseButtons.Left)
            {
                ctrl.OnLeftButtonUp(p);
            }
            else if(e.Button == MouseButtons.Right)
            {
                ctrl.OnRightButtonUp(p);
            }
        }

        private void Panel_MouseMove(object sender, MouseEventArgs e)
        {
            var p = PositionInScreen(e.Location);
            if (e.Button == MouseButtons.Left)
            {
                ctrl.OnLeftButtonDragging(p);
            }
            else if(e.Button == MouseButtons.Right)
            {
                ctrl.OnRightButtonDragging(p);
            }
        }

        private void Panel_MouseDown(object sender, MouseEventArgs e)
        {
            var p = PositionInScreen(e.Location);
            if (e.Button == MouseButtons.Left)
            {
                ctrl.OnLeftButtonDown(p);
            }
            else if(e.Button == MouseButtons.Right)
            {
                ctrl.OnRightButtonDown(p);
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
            this.adapter.Render(Panel.Width, Panel.Height);
            //throw new NotImplementedException();
        }

        private void OnPaint(object sender, PaintEventArgs e)
        {
            this.adapter.Render(Panel.Width, Panel.Height);
        }
       
    }
}
