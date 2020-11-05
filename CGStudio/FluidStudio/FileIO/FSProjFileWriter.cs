using FluidStudio.Physics;
using System.Xml.Linq;

namespace FluidStudio.FileIO
{
    public class FSProjFile    
    {
        public const string RootLabel = "FluidStudio";
        public const string PhysicsSceneLabel = "PhysicsScene";
        public const string NameLabel = "Name";
    }

    public class FSProjFileWriter
    {
        private int version = 1;

        public FSProjFileWriter()
        {
        }

        public XElement Write(MainModel model)
        {
            var root = new XElement(FSProjFile.RootLabel);
            root.Add(new XElement("FileFormatVersion", version));
            foreach (var scene in model.PhysicsModel.Scenes)
            {
                root.Add( Write(scene) );
            }
            return root;
        }

        public XElement Write(PhysicsScene scene)
        {
            var root = new XElement(FSProjFile.PhysicsSceneLabel);
            root.Add(new XElement(FSProjFile.NameLabel, scene.Name.Value));
            foreach (var fluid in scene.Fluids)
            {
                root.Add(new XElement("Name", fluid.Name));
                root.Add(new XElement("Id", fluid.Id));
                root.Add(new XElement("Stiffness", fluid.Stiffness));
                root.Add(new XElement("Viscosity", fluid.Viscosity));
            }
            return root;
        }
    }
}
