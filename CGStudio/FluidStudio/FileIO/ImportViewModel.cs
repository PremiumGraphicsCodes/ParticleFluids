using FluidStudio.VDB;
using Microsoft.Win32;
using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.FileIO
{
    public class ImportViewModel
    {
        public ReactiveCommand ImportCommand { get; }
            = new ReactiveCommand();

        private readonly VDBModel vdb;

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        public ImportViewModel(MainModel mainModel, SceneList scenes, Canvas3d canvas)
        {
            this.vdb = mainModel.VDBModel;
            this.world = scenes;
            this.canvas = canvas;
            ImportCommand.Subscribe(OnImport);
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
                var newIds = vdb.Read(filePath, world);
                foreach(var newId in newIds)
                {
                    var scene = new SceneModel();
                    scene.Id.Value = newId;
                    var type = vdb.GetVDBType(newId, world);
                    if(type == VDBModel.VDBType.Point)
                    {
                        scene.SceneType = new PG.Core.SceneType("VDBPoints");
                        world.Scenes.Add(scene);
                    }
                }
                return newIds;
            }
            else if (ext == ".obj")
            {
                var newId = vdb.ReadOBJ(world, filePath);

                var scene = new SceneModel();
                scene.Id.Value = newId;
                scene.SceneType = new PG.Core.SceneType("VDBMesh");
                world.Scenes.Add(scene);

                var newIds = new List<int>();
                newIds.Add(newId);
                return newIds;
            }
            else
            {
                return new List<int>();
            }
        }

    }
}
