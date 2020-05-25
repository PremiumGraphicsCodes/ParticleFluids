using Fluent;
using System.Windows;

namespace PG.CGStudio
{
    public partial class MainWindow : RibbonWindow
    {
        public MainWindow()
        {
            InitializeComponent();

            /*
            ContentRendered += (s, e) =>
            {
                var dialog = new ControlView();
                dialog.Owner = this;
                dialog.Show();
            };
            */
        }

        private void Grid_Initialized(object sender, System.EventArgs e)
        {
        }

        private void RibbonWindow_Initialized(object sender, System.EventArgs e)
        {
            var dataContext = this.DataContext as MainWindowViewModel;
            var canvas = dataContext.Canvas;
            HwndHostPresenter.SetCanvas(canvas);

        }
    }
}
