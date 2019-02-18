﻿using System;
using System.Windows.Controls;
using System.Windows.Forms;
using System.Windows.Interop;
using PG.Core.Math;

namespace PG.CGStudio
{
    public partial class Canvas3dView : System.Windows.Controls.UserControl
    {
        private static Canvas3dView instance;
        private UICtrl.IUICtrl ctrl;

        public static Canvas3dView Instance
        {
            get { return instance; }
        }

        public void Render()
        {
            renderer.Render(Panel.Width, Panel.Height);
        }

        public void Update(Repository model)
        {
            renderer.Update(model.Adapter);
        }

        private PG.CLI.Renderer renderer;

        public PG.CLI.Renderer Renderer { get { return renderer; } }

        public Canvas3dView()
        {
            instance = this;
            InitializeComponent();
        }

        private void WindowsFormsHost_Initialized(object sender, System.EventArgs e)
        {
            this.renderer = new PG.CLI.Renderer(Panel.Handle);
            this.renderer.Build(Repository.Instance.Adapter);
            this.ctrl = new UICtrl.CameraUICtrl(renderer.camera);
            Panel.Paint += OnPaint;
            Panel.Resize += OnResize;
            Panel.MouseDown += Panel_MouseDown;
            Panel.MouseUp += Panel_MouseUp;
            Panel.MouseMove += Panel_MouseMove;
            Panel.MouseWheel += Panel_MouseWheel;
        }

        private void Panel_MouseWheel(object sender, MouseEventArgs e)
        {
            ctrl.OnWheel(e.Delta / 1200.0f);
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
            this.renderer.Render(Panel.Width, Panel.Height);
            //throw new NotImplementedException();
        }

        private void OnPaint(object sender, PaintEventArgs e)
        {
            this.renderer.Render(Panel.Width, Panel.Height);
        }
       
    }
}
