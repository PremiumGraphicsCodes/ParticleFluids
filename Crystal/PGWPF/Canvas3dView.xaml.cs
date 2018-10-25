using System.Windows.Controls;

namespace PGWPF
{
    public partial class Canvas3dView : UserControl
    {
        private PGCLI.OpenGLSimpleAdapter adapter;

        public Canvas3dView()
        {
            InitializeComponent();
            Loaded += (s, e) => {
                var handle = Host.Handle;               
                adapter = new PGCLI.OpenGLSimpleAdapter(handle);
            };
        }

    }
}
