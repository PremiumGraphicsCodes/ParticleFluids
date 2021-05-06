using FluidStudio.Physics;
using FluidStudio.Physics.Fluid;
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
        public const string ParticleRadiusLabel = "ParticleRadius";
        public const string DensityLabel = "Density";
        public const string StiffnessLabel = "Stiffness";
        public const string ViscosityLabel = "Viscosity";
        public const string IsBoundarylabel = "IsBoundary";
        public const string DoExportVDBLabel = "ExportVDB";
        public const string ExportDirectory = "ExportDirectory";

        public const string EmitterSceneLabel = "EmitterScene";
        public const string StartStepLabel = "StartStep";
        public const string EndStepLabel = "EndStep";
        public const string IntervalLabel = "Interval";
        public const string InitialVelocityLabel = "InitialVelocity";

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
            foreach(var emitter in scene.Emitters)
            {
                root.Add(CreateElement(emitter));
            }
            foreach(var boundary in scene.Boundaries)
            {
                root.Add(CreateElement(FSProjFile.CSGBoundarySceneLabel, boundary));
            }
            return root;
        }

        private XElement CreateElement(FluidScene fluid)
        {
            var e = new XElement(FSProjFile.FluidSceneLabel);
            e.Add(new XAttribute(FSProjFile.NameLabel, fluid.Name));
            e.Add(new XElement(FSProjFile.ParticlesFilePathLabel, fluid.ParticleFilePath));
            e.Add(new XElement(FSProjFile.ParticleRadiusLabel, fluid.ParticleRadius));
            e.Add(new XElement(FSProjFile.DensityLabel, fluid.Density));
            e.Add(new XElement(FSProjFile.StiffnessLabel, fluid.Stiffness));
            e.Add(new XElement(FSProjFile.ViscosityLabel, fluid.Viscosity));
            e.Add(new XElement(FSProjFile.IsBoundarylabel, fluid.IsBoundary));
            e.Add(new XElement(FSProjFile.DoExportVDBLabel, fluid.ExportModel.DoExportVDB));
            e.Add(new XElement(FSProjFile.ExportDirectory, fluid.ExportModel.VDBExportDirectory));
            return e;
        }

        private XElement CreateElement(EmitterScene emitter)
        {
            var e = new XElement(FSProjFile.EmitterSceneLabel);
            e.Add(new XAttribute(FSProjFile.NameLabel, emitter.Name));
            e.Add(new XElement(FSProjFile.ParticlesFilePathLabel, emitter.ParticleFilePath));
            e.Add(new XElement(FSProjFile.ParticleRadiusLabel, emitter.ParticleRadius));
            e.Add(new XElement(FSProjFile.DensityLabel, emitter.Density));
            e.Add(new XElement(FSProjFile.StiffnessLabel, emitter.Stiffness));
            e.Add(new XElement(FSProjFile.ViscosityLabel, emitter.Viscosity));
            e.Add(CreateElement(FSProjFile.InitialVelocityLabel, emitter.InitialVelocity));
            e.Add(new XElement(FSProjFile.StartStepLabel, emitter.StartTimeStep));
            e.Add(new XElement(FSProjFile.EndStepLabel, emitter.EndTimeStep));
            e.Add(new XElement(FSProjFile.IntervalLabel, emitter.Interval));
            e.Add(new XElement(FSProjFile.DoExportVDBLabel, emitter.ExportModel.DoExportVDB));
            e.Add(new XElement(FSProjFile.ExportDirectory, emitter.ExportModel.VDBExportDirectory));
            return e;
        }

        private XElement CreateElement(string name, CSGBoundaryScene boundary)
        {
            var e = new XElement(name);
            e.Add(new XAttribute(FSProjFile.NameLabel, boundary.Name));
            e.Add(CreateElement(FSProjFile.Box3dLabel, boundary.BoundingBox));
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
