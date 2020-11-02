using FluidStudio.Physics;
using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Packaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace FluidStudio.FileIO
{
    public class FSProjFileWriter
    {
        private int version = 1;

        public FSProjFileWriter()
        {
        }
        void Write(string filePath, MainModel model)
        {
            var doc = new XmlDocument();
            var rootElement = doc.CreateElement("FSProj");
            doc.AppendChild(rootElement);
//            doc.CreateElement("Version",)
            doc.Save(filePath);

        }
    }
}
