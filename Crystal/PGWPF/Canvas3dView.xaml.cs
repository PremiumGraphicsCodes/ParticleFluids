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
        private UICtrl ctrl;

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
            this.ctrl = new CameraUICtrl(adapter.camera);
            Panel.Paint += OnPaint;
            Panel.Resize += OnResize;
            Panel.MouseDown += Panel_MouseDown;
        }

        private void Panel_MouseDown(object sender, MouseEventArgs e)
        {
            ctrl.OnLeftButtonDown(new Vector2d(0,0));
            /*
            if(e.Button == MouseButtons.Left)
            {
                var p = e.Location;
                ctrl.OnLeftButtonDown();
            }
            */
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

        private void WindowsFormsHost_SizeChanged(object sender, System.Windows.SizeChangedEventArgs e)
        {

        }

        private void Host_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            var p = e.GetPosition(this);
 //           ctrl.OnLeftButtonDown();
        }

        private void Host_MouseLeftButtonUp(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {

        }

        private void Host_MouseRightButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {

        }

        private void Host_MouseRightButtonUp(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {

        }
    }
}
