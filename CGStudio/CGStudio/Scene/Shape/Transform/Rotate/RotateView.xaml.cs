using System.Windows.Controls;
using System.Windows.Input;

namespace PG.CGStudio.Scene.Shape.Transform.Rotate
{
    public partial class RotateView : UserControl
    {
        public RotateView()
        {
            InitializeComponent();
        }

        private void Vector3dView_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                var vm = DataContext as RotateViewModel;
                var model = vm.Model;
                model.SetMatrix(true);
            }
        }
    }
}
