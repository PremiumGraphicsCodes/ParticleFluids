using System;
using System.Windows;
using System.Windows.Input;

namespace PG.CGStudio
{
    public partial class OpenGLAdornment : System.Windows.Controls.UserControl
    {
        public OpenGLAdornment()
        {
            InitializeComponent();

   //         this.KeyDown += keyDown;
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            var window = Window.GetWindow(this);
            window.KeyDown += HandleKeyPress;
        }

        private void HandleKeyPress(object sender, KeyEventArgs e)
        {
            Canvas3d.Instance.UICtrl.OnKeyDown(e.Key);
            //Do work
        }
    }
}
