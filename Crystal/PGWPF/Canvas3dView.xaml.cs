using System.Windows.Controls;
using System.Windows.Forms;
using System.Windows.Interop;

namespace PGWPF
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

        private PGCLI.OpenGLSimpleAdapter adapter;

        public Canvas3dView()
        {
            instance = this;
            InitializeComponent();
            /*
            Loaded += (s, e) => {
                var handle = Host.Handle;               
                adapter = new PGCLI.OpenGLSimpleAdapter(handle);
                adapter.Render();
            };
            */
        }
    }
}
