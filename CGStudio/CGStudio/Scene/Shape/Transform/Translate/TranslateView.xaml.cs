using System.Windows.Controls;

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
            var vm = DataContext as TranslateViewModel;
            var model = vm.Model;
            model.SetMatrix(true);
        }
    }
}
