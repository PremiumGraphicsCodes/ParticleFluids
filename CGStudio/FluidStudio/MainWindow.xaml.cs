using System;
using System.Windows.Controls.Ribbon;

namespace FluidStudio
{
    public partial class MainWindow : RibbonWindow
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Initialized(object sender, EventArgs e)
        {
            var dataContext = this.DataContext as MainWindowViewModel;
            var canvas = dataContext.Canvas;
            HwndHostPresenter.SetCanvas(canvas);

        }
    }
}
