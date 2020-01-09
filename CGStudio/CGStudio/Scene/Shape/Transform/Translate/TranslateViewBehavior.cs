using System.Windows.Interactivity;

namespace PG.CGStudio.Scene.Shape.Transform
{
    class TranslateViewBehavior : Behavior<TranslateView>
    {
        protected override void OnAttached()
        {
            base.OnAttached();
            base.AssociatedObject.PreviewKeyDown += AssociatedObject_PreviewKeyDown;
        }

        protected override void OnDetaching()
        {
            base.OnDetaching();
            this.AssociatedObject.PreviewKeyDown -= AssociatedObject_PreviewKeyDown;
        }

        private void AssociatedObject_PreviewKeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (e.Key == System.Windows.Input.Key.Enter)
            {
                var view = sender as TranslateView;
                var vm = view.DataContext as TranslateViewModel;
                var model = vm.Model;
                model.SetMatrix(true);
            }
        }
    }
}
