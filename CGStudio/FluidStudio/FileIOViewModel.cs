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

        public ReactiveCommand ImportCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand ExportCommand { get; }
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
            ImportCommand.Subscribe(OnImport);
            ExportCommand.Subscribe(OnExport);
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

        private void OnImport()
        {
            var dialog = new OpenFileDialog
            {
                Title = "Import",
                Filter = "OBJFile(*.obj)|*.obj|OpenVDBFile(*.vdb)|*.vdb|AllFiles(*.*)|*.*",
            };
            if (dialog.ShowDialog() == true)
            {
                var fileName = dialog.FileName;
                var newIds = Import(dialog.FileName);
                foreach (var id in newIds)
                {
                    canvas.BuildShader(world, id);
                }
                canvas.Render();
            }
        }

        private List<int> Import(string filePath)
        {
            var ext = System.IO.Path.GetExtension(filePath);
            if (ext == ".vdb")
            {
                var newIds = model.VDBModel.Read(filePath, world);
                foreach(var newId in newIds)
                {
                    var scene = new SceneModel();
                    scene.Id.Value = newId;
                    scene.SceneType = new PG.Core.SceneType(VDBModel.VDBPointType);
                    model.Scenes.Add(scene);
                }
                return newIds;
            }
            else if(ext == ".obj")
            {
                var newId = model.VDBModel.ReadOBJ(world, filePath);

                var scene = new SceneModel();
                scene.Id.Value = newId;
                scene.SceneType = new PG.Core.SceneType(VDBModel.VDBMeshType);
                model.Scenes.Add(scene);

                var newIds = new List<int>();
                newIds.Add(newId);
                return newIds;
            }
            else
            {
                return new List<int>();
            }
        }

        private void OnExport()
        {
            /*
            var dialog = new SaveFileDialog
            {
                Title = "Export",
                Filter = "OpenVDBFile(*.vdb)|*.vdb|AllFiles(*.*)|*.*",
            };
            if (dialog.ShowDialog() == true)
            {
                if (Export(dialog.FileName))
                {
                    MessageBox.Show("Export Suceeded");
                }
                else
                {
                    MessageBox.Show("Export Failed");
                }
            }
            */
        }
    }
}