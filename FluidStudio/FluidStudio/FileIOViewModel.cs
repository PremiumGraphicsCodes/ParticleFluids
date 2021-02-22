using FluidStudio.FileIO;
using FluidStudio.VDB;
using Microsoft.Win32;
using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;
using System.Collections.Generic;
using System.Linq;
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

        public ReactiveCommand ExportCommand { get; }
            = new ReactiveCommand();

        private readonly MainModel model;

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        private string currentFilePath = "";

        public FileIOViewModel(MainModel model, SceneList world, Canvas3d canvas)
        {
            this.model = model;
            this.world = world;
            this.canvas = canvas;
            NewCommand.Subscribe(OnNew);
            OpenCommand.Subscribe(OnOpen);
            SaveCommand.Subscribe(OnSave);
            SaveAsCommand.Subscribe(OnSaveAs);
            ExportCommand.Subscribe(OnExport);
        }

        private void OnNew()
        {
            world.Scenes.Clear();
            model.PhysicsModel.Clear();
            canvas.Renderer.Build(world.Adapter);
            canvas.Update();
            canvas.Render();
            this.currentFilePath = "";
        }

        private void OnOpen()
        {
            var dialog = new OpenFileDialog
            {
                Title = "Open",
                Filter = "FSSceneFile(*.fsscene)|*.fsscene|AllFiles(*.*)|*.*",
            };
            if (dialog.ShowDialog() == true)
            {
                model.PhysicsModel.Solvers.Clear();
                var reader = new FSSceneFileReader();
                reader.Read(model, canvas, dialog.FileName);
                this.currentFilePath = dialog.FileName;
            }
        }

        private void OnSave()
        {
            if (!string.IsNullOrEmpty(this.currentFilePath))
            {
                var writer = new FSSceneFileWriter();
                writer.Write(model, currentFilePath);
                return;
            }
            OnSaveAs();
        }

        private void OnSaveAs()
        {
            var dialog = new SaveFileDialog
            {
                Title = "Save",
                Filter = "FSSceneFile(*.fsscene)|*.fsscene|AllFiles(*.*)|*.*",
            };
            if (dialog.ShowDialog() == true)
            {
                var writer = new FSSceneFileWriter();
                writer.Write(model, dialog.FileName);
            }
        }

        private void OnExport()
        {
            var dialog = new SaveFileDialog
            {
                Title = "Export",
                Filter = "OpenVDBFile(*.vdb)|*.vdb|AllFiles(*.*)|*.*",
            };
            if(dialog.ShowDialog() == true)
            {
                var path = dialog.FileName;
                var ext = System.IO.Path.GetExtension(path);
                if (ext == ".vdb") {
                    model.VDBModel.ExportAll(model.Scenes, path);
                }
            }
        }
    }
}