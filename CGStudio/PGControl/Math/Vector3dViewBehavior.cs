using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Interactivity;

namespace PG.Control.Math
{
    class Vector3dViewBehavior : Behavior<TextBox>
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

        private void OnPreviewKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                // エンターキーが押されたら BindingをUpdateする
                var view = (TextBox)sender;
                DependencyProperty prop = TextBox.TextProperty;
                BindingExpression binding
                 = BindingOperations.GetBindingExpression(view, prop);
                if (binding != null)
                {
                    binding.UpdateSource();
                }
            }
        }
    }
}
