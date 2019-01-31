using Fluent;
using System.Windows;

namespace PG.CGStudio
{
    public partial class MainWindow : RibbonWindow
    {
        public MainWindow()
        {
            InitializeComponent();

            ContentRendered += (s, e) =>
            {
                var dialog = new ControlView();
                dialog.Owner = this;
                dialog.Show();
            };
        }        
    }
}
