using FluidStudio.Physics;
using PG.Core.Math;
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
        public const string EffectLengthLabel = "EffectLength";
        public const string TimeStepLabel = "TimeStep";
        public const string FluidSceneLabel = "FluidScene";
        public const string IdLabel = "Id";
        public const string ParticlesFilePathLabel = "ParticlesFilePath";
        public const string DensityLabel = "Density";
        public const string StiffnessLabel = "Stiffness";
        public const string ViscosityLabel = "Viscosity";
        public const string IsBoundarylabel = "IsBoundary";
        public const string DoExportVDBLabel = "ExportVDB";
        public const string ExportDirectory = "ExportDirectory";

        public const string CSGBoundarySceneLabel = "CSGBoundaryScene";
        public const string Box3dLabel = "Box3d";
        public const string Vector3dLabel = "Vector3d";
        public const string XLabel = "X";
        public const string YLabel = "Y";
        public const string ZLabel = "Z";
    }

    public class FSSceneFileWriter
    {
        private int version = 1;

        public FSSceneFileWriter()
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
            root.Add(new XElement(FSProjFile.TimeStepLabel, scene.TimeStep));
            root.Add(new XElement(FSProjFile.EffectLengthLabel, scene.EffectLength));
            foreach (var fluid in scene.Fluids)
            {
                root.Add(CreateElement(fluid));
            }
            foreach(var boundary in scene.CSGBoundaries)
            {
                root.Add(CreateElement("CSGBoundary", boundary));
            }
            return root;
        }

        private XElement CreateElement(FluidScene fluid)
        {
            var froot = new XElement(FSProjFile.FluidSceneLabel);
            froot.Add(new XAttribute(FSProjFile.NameLabel, fluid.Name));
            froot.Add(new XElement(FSProjFile.ParticlesFilePathLabel, fluid.ParticleFilePath));
            froot.Add(new XElement(FSProjFile.DensityLabel, fluid.Density));
            froot.Add(new XElement(FSProjFile.StiffnessLabel, fluid.Stiffness));
            froot.Add(new XElement(FSProjFile.ViscosityLabel, fluid.Viscosity));
            froot.Add(new XElement(FSProjFile.IsBoundarylabel, fluid.IsBoundary));
            froot.Add(new XElement(FSProjFile.DoExportVDBLabel, fluid.ExportModel.DoExportVDB));
            froot.Add(new XElement(FSProjFile.ExportDirectory, fluid.ExportModel.VDBExportDirectory));
            return froot;
        }

        private XElement CreateElement(string name, CSGBoundaryScene boundary)
        {
            var e = new XElement(name);
            e.Add(new XAttribute(FSProjFile.NameLabel, boundary.Name));
            e.Add(CreateElement("Box", boundary.BoundingBox));
            return e;
        }

        private XElement CreateElement(string name, Box3d box)
        {
            var e = new XElement(name);
            e.Add(CreateElement("Min", box.Min));
            e.Add(CreateElement("Max", box.Max));
            return e;
        }

        private XElement CreateElement(string name, Vector3d v)
        {
            var e = new XElement(name);
            e.Add(new XElement("X", v.X));
            e.Add(new XElement("Y", v.Y));
            e.Add(new XElement("Z", v.Z));
            return e;
        }
    }
}
