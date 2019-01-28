using System.Windows;

namespace PG.CGStudio
{
    public partial class MainWindow : Window
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
