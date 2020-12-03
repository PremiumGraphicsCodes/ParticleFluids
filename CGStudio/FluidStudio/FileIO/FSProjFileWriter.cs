using FluidStudio.Physics;
using System.Collections.Specialized;
using System.Xml.Linq;

namespace FluidStudio.FileIO
{
    public class FSProjFile    
    {
        public const string RootLabel = "FluidStudio";
        public const string FileFormatVersionLabel = "FileFormatVersion";
        public const string PhysicsSceneLabel = "PhysicsScene";
        public const string NameLabel = "Name";
        public const string IdLabel = "Id";
        public const string ParticleSystemIdLabel = "ParticleSystemId";
        public const string StiffnessLabel = "Stiffness";
        public const string ViscosityLabel = "Viscosity";
    }

    public class FSProjFileWriter
    {
        private int version = 1;

        public FSProjFileWriter()
        {
        }

        public void Write(MainModel model, string filePath)
        {
            var elem = Write(model);
            elem.Save(filePath);
        }

        public XElement Write(MainModel model)
        {
            var root = new XElement(FSProjFile.RootLabel);
            root.Add(new XAttribute(FSProjFile.FileFormatVersionLabel, version));
            foreach (var scene in model.PhysicsModel.Solvers)
            {
                root.Add( Write(scene) );
            }
            return root;
        }

        public XElement Write(SolverScene scene)
        {
            var root = new XElement(FSProjFile.PhysicsSceneLabel);
            root.Add( new XAttribute(FSProjFile.NameLabel, scene.Name) );
            foreach (var fluid in scene.Fluids)
            {
                root.Add(new XElement(FSProjFile.IdLabel, fluid.Id));
                root.Add(new XElement(FSProjFile.NameLabel, fluid.Name));
                root.Add(new XElement(FSProjFile.ParticleSystemIdLabel, fluid.SourceParticleSystemId));
                root.Add(new XElement(FSProjFile.StiffnessLabel, fluid.Stiffness));
                root.Add(new XElement(FSProjFile.ViscosityLabel, fluid.Viscosity));
            }
            return root;
        }
    }
}
