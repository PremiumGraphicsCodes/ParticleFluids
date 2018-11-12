﻿using System;
using System.Windows.Controls;
using System.Windows.Forms;
using System.Windows.Interop;

namespace PG.CGStudio
{
    public partial class Canvas3dView : System.Windows.Controls.UserControl
    {
        private static Canvas3dView instance;

        public static Canvas3dView Instance
        {
            get { return instance; }
        }

        public void Render()
        {
            adapter.Render();
        }

        private PG.CLI.Renderer adapter;

        public Canvas3dView()
        {
            instance = this;
            InitializeComponent();
        }

        private void WindowsFormsHost_Initialized(object sender, System.EventArgs e)
        {
            this.adapter = new PG.CLI.Renderer(Panel.Handle);
            Panel.Paint += OnPaint;
            Panel.Resize += OnResize;
        }

        private void OnResize(object sender, EventArgs e)
        {
            //throw new NotImplementedException();
        }

        private void OnPaint(object sender, PaintEventArgs e)
        {
            this.adapter.Render();
        }

        private void WindowsFormsHost_SizeChanged(object sender, System.Windows.SizeChangedEventArgs e)
        {

        }
    }
}
