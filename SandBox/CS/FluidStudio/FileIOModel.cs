using FluidStudio.FileIO;
using PG.Control.OpenGL;
using System;

namespace FluidStudio
{
    public class FileIOModel
    {
        private string currentFilePath = "";

        public string CurrentFilePath
        {
            get
            {
                return currentFilePath;
            }
            set {
                this.currentFilePath = value;
                System.Environment.CurrentDirectory = System.IO.Path.GetDirectoryName(value);
            }
        }

        private MainModel mainModel;

        public FileIOModel(MainModel model)
        {
            this.mainModel = model;
        }

        public void New()
        {
            this.currentFilePath = "";
//            System.Environment.CurrentDirectory = "";
        }

        public void Open(string filePath, Canvas3d canvas)
        {
            this.CurrentFilePath = filePath;
            mainModel.PhysicsModel.Solvers.Clear();
            var reader = new FSSceneFileReader();
            reader.Read(mainModel, canvas, filePath);
            canvas.Camera.Fit();
            canvas.Render();
        }

        public void Save()
        {
            var writer = new FSSceneFileWriter();
            writer.Write(mainModel, CurrentFilePath);
        }

        public void SaveAs(string filePath)
        {
            var writer = new FSSceneFileWriter();
            writer.Write(mainModel, filePath);
            this.CurrentFilePath = filePath;
        }

        private string GetWorkingDirectory()
        {
            return System.Environment.CurrentDirectory;
            /*
            if (string.IsNullOrEmpty(CurrentFilePath))
            {
                return System.IO.Directory.GetCurrentDirectory();
            }
            return System.IO.Path.GetDirectoryName(CurrentFilePath);
            */
        }

        public string ToFullPath(string path)
        {
            var isRootPath = System.IO.Path.IsPathRooted(path);
            if(isRootPath)
            {
                return path;
            }
            return System.IO.Path.GetFullPath(path);
            //var baseUri1 = new Uri(GetWorkingDirectory());
            //return new Uri(baseUri1, path).LocalPath;
        }

        public string ToRelativePath(string fullPath)
        {
            var baseUri = new Uri(GetWorkingDirectory());
            var fullUri = new Uri(fullPath);
            var uri = baseUri.MakeRelativeUri(fullUri);
            return uri.ToString();
        }
    }
}
