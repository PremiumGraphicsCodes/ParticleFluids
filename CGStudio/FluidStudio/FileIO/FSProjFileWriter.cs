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
        public const string TimeStepLabel = "TimeStep";
        public const string FluidSceneLabel = "FluidScene";
        public const string IdLabel = "Id";
        public const string ParticleSystemIdLabel = "ParticleSystemId";
        public const string StiffnessLabel = "Stiffness";
        public const string ViscosityLabel = "Viscosity";
        public const string IsBoundarylabel = "IsBoundary";
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
                root.Add(Write(scene));
            }
            return root;
        }

        public XElement Write(SolverScene scene)
        {
            var root = new XElement(FSProjFile.PhysicsSceneLabel);
            root.Add(new XAttribute(FSProjFile.NameLabel, scene.Name));
            root.Add(new XAttribute(FSProjFile.TimeStepLabel, scene.TimeStep));
            foreach (var fluid in scene.Fluids)
            {
                root.Add(CreateElement(fluid));
            }
            return root;
        }

        private XElement CreateElement(FluidScene fluid)
        {
            var froot = new XElement(FSProjFile.FluidSceneLabel);
            froot.Add(new XElement(FSProjFile.IdLabel, fluid.Id));
            froot.Add(new XElement(FSProjFile.NameLabel, fluid.Name));
            froot.Add(new XElement(FSProjFile.ParticleSystemIdLabel, fluid.SourceParticleSystemId));
            froot.Add(new XElement(FSProjFile.StiffnessLabel, fluid.Stiffness));
            froot.Add(new XElement(FSProjFile.ViscosityLabel, fluid.Viscosity));
            froot.Add(new XElement(FSProjFile.IsBoundarylabel, fluid.IsBoundary));
            return froot;
        }
    }
}
