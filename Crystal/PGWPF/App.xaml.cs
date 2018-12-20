﻿using System.Windows;

namespace PG.CGStudio
{
    public partial class App : Application
    {
        private MainModel model;

        protected override void OnStartup(StartupEventArgs e)
        {
            this.model = new MainModel();

            var dialog = new Generation.GenerationView();
//            dialog.Owner = Application.Current.MainWindow;
            dialog.Show();
        }
    }
}
