using System;
using System.Windows;
using System.Windows.Controls;
using HwndExtensions.Host;

namespace PG.CGStudio
{
    public class OpenGLPresenter : HwndHostPresenter
    {
        public OpenGLPresenter()
        {
            var browser = new WebBrowser();
            //browser.Source = new Uri("http://blogs.microsoft.co.il/michaels/2014/11/28/wpf-hwnd-adorner/");

            HwndHost = browser;
            RegisterToAppShutdown();
        }

        private void RegisterToAppShutdown()
        {
            Application.Current.Dispatcher.ShutdownStarted += OnShutdownStarted;
        }

        private void OnShutdownStarted(object sender, EventArgs e)
        {
            Dispose();
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                var host = HwndHost;
                if (host != null)
                    host.Dispose();
            }
        }        
    }
}
