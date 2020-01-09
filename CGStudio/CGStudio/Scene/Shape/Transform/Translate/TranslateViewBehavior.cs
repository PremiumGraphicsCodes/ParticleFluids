using PG.Control.Math;
using System.Windows.Interactivity;

namespace PG.CGStudio.Scene.Shape.Transform
{
    public class TranslateViewBehavior : Behavior<TranslateView>
    {
        protected override void OnAttached()
        {
            base.OnAttached();
            this.AssociatedObject.PreviewKeyDown += OnPreviewKeyDown;
        }

        protected override void OnDetaching()
        {
            base.OnDetaching();
            this.AssociatedObject.PreviewKeyDown -= OnPreviewKeyDown;
        }

        private void OnPreviewKeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (e.Key == System.Windows.Input.Key.Enter)
            {
                var view = sender as TranslateView;
                var vm = view.DataContext as TranslateViewModel;
                var model = vm.Model;
                model.SetMatrix(true);
                /*
                var prop = view.DataContext;
                BindingExpression binding
                    = BindingOperations.GetBindingExpression(tBox, prop);
                if (binding != null) { binding.UpdateSource(); }
                */
            }
        }
    }
}
