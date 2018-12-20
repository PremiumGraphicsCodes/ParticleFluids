using System;
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
            adapter.Render(Panel.Width, Panel.Height);
        }

        public void Update(MainModel model)
        {
            adapter.Update(model.Adapter);
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
    }
}
