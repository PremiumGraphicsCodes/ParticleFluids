using FluidStudio.VDB;
using Microsoft.Win32;
using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;
using System.Collections.Generic;
using System.Windows;

namespace FluidStudio
{
    public class FileIOViewModel
    {
        public ReactiveCommand NewCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand OpenCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand SaveCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand SaveAsCommand { get; }
            = new ReactiveCommand();

        private readonly MainModel model;

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        public FileIOViewModel(MainModel model, SceneList world, Canvas3d canvas)
        {
            this.model = model;
            this.world = world;
            this.canvas = canvas;
            NewCommand.Subscribe(OnNew);
            OpenCommand.Subscribe(OnOpen);
            SaveCommand.Subscribe(OnSave);
            SaveAsCommand.Subscribe(OnSaveAs);
        }

        private void OnNew()
        {
            /*
            world.Scenes.Clear();
            canvas.Renderer.Build(world.Adapter);
            canvas.Update();
            canvas.Render();
            */
        }

        private void OnOpen()
        {
            PG.CLI.PhysicsCommand command = new PG.CLI.PhysicsCommand();
            command.Create(PG.ParticleSystemCreateLabels.ParticleSystemAddLabel);
            command.Execute(world.Adapter);

            var dialog = new OpenFileDialog
            {
                Title = "Open",
                Filter = "FSProjectFile(*.fsproj)|*.fsproj|AllFiles(*.*)|*.*",
            };
            if (dialog.ShowDialog() == true)
            {
                //world.Open(dialog.FileName);
            }
        }

        private void OnSave()
        {
            var dialog = new SaveFileDialog
            {
                Title = "Save",
                Filter = "FSProjectFile(*.fsproj)|*.fsproj|AllFiles(*.*)|*.*",
            };
            if (dialog.ShowDialog() == true)
            {
                //world.Save(dialog.FileName);
            }
        }

        private void OnSaveAs()
        {
            var dialog = new SaveFileDialog
            {
                Title = "SaveAs"
            };
            if (dialog.ShowDialog() == true)
            {
                //world.Save(dialog.FileName);
            }
        }
    }
}