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
            var vm = DataContext as ScaleViewModel;
            var model = vm.Model;
//            model.SetMatrix(true);
        }
    }
}
