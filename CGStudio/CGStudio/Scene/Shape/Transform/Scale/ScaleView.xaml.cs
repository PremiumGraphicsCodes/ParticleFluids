using System.Windows.Controls;

namespace PG.CGStudio.Scene.Shape.Transform.Scale
{
    public partial class ScaleView : UserControl
    {
        public ScaleView()
        {
            InitializeComponent();
        }

        private void Vector3dView_KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (e.Key == System.Windows.Input.Key.Enter)
            {
                var vm = DataContext as ScaleViewModel;
                vm.SetMatrix(true);
            }
        }
    }
}
