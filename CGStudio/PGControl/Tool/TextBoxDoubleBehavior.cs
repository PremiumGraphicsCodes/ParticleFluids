using System.Windows;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Interactivity;

namespace PG.Control
{
    class TextBoxDoubleBehavior: Behavior<TextBoxDouble>
    {
        protected override void OnAttached()
        {
            base.OnAttached();
            this.AssociatedObject.PreviewKeyDown += OnPreviewKeyDown;
            this.AssociatedObject.GotFocus += OnGotFocus;
        }

        protected override void OnDetaching()
        {
            base.OnDetaching();
            this.AssociatedObject.PreviewKeyDown -= OnPreviewKeyDown;
            this.AssociatedObject.GotFocus += OnGotFocus;
        }

        private void OnPreviewKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                // エンターキーが押されたら BindingをUpdateする
                var view = (TextBoxDouble)sender;
                DependencyProperty prop = TextBoxDouble.TextProperty;
                BindingExpression binding
                 = BindingOperations.GetBindingExpression(view, prop);
                if (binding != null)
                {
                    binding.UpdateSource();
                }
            }
        }

        private void OnGotFocus(object sender, RoutedEventArgs e)
        {
            var view = (TextBoxDouble)sender;
            view.SelectAll();
        }
    }
}
