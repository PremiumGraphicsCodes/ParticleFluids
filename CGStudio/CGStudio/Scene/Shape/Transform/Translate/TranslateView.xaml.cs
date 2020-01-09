using PG.Control.Math;
using System.Windows.Controls;
using System.Windows.Data;

namespace PG.CGStudio.Scene.Shape.Transform
{
    public partial class TranslateView : UserControl
    {
        public TranslateView()
        {
            InitializeComponent();
        }

        private void Vector3dView_KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (e.Key == System.Windows.Input.Key.Enter)
            {
                var vm = DataContext as TranslateViewModel;
                vm.SetMatrix(true);
            }
        }
    }
}
