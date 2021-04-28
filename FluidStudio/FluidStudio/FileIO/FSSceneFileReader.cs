using FluidStudio.Physics;
using FluidStudio.Physics.Fluid;
using PG.Control.OpenGL;
using PG.Core.Math;
using System.Collections.Generic;
using System.Xml.Linq;

namespace FluidStudio.FileIO
{
    public class FSSceneFileReader
    {
        public void Read(MainModel model, Canvas3d canvas, string filePath)
        {
            var elem = XElement.Load(filePath);
            Read(model, canvas, elem);
        }

        public void Read(MainModel model, Canvas3d canvas, XElement root)
        {
            //            var root = elem.Element(FSProjFile.RootLabel);
            var version = root.Attribute(FSProjFile.FileFormatVersionLabel).Value;
            var physicsElem = root.Element(FSProjFile.PhysicsSceneLabel);
            ReadPhysicsScene(model, canvas, physicsElem);
        }

        private void ReadPhysicsScene(MainModel model, Canvas3d canvas, XElement elem)
        {
            var solver = new SolverScene(model.Scenes);
            var effectLength = float.Parse(elem.Element(FSProjFile.EffectLengthLabel).Value);
            var timeStep = float.Parse(elem.Element(FSProjFile.TimeStepLabel).Value);
            var scenes = elem.Elements(FSProjFile.FluidSceneLabel);
            foreach (var scene in scenes)
            {
                var fluid = ReadFluidScene(model, canvas, scene, solver);
                solver.Add(fluid);
            }
            var emitters = elem.Elements(FSProjFile.EmitterSceneLabel);
            foreach(var emitter in emitters)
            {
                var e = ReadEmitterScene(model, canvas, emitter, solver);
                solver.Add(e);
            }
            var bElements = elem.Elements(FSProjFile.CSGBoundarySceneLabel);
            foreach (var bElem in bElements)
            {
                var bScene = ReadCSGBoundaryScene(model, canvas, bElem, solver);
                solver.Add(bScene);
            }
            var name = elem.Attribute(FSProjFile.NameLabel).Value;
            solver.TimeStep = timeStep;
            solver.EffectLength = effectLength;
            solver.TimeStep = timeStep;
            solver.Name = name;
            solver.Send();
            model.PhysicsModel.Solvers.Add(solver);
        }

        private FluidScene ReadFluidScene(MainModel model, Canvas3d canvas, XElement elem, SolverScene parent)
        {
            var name = elem.Attribute(FSProjFile.NameLabel).Value;
            //            var id = int.Parse(elem.Element(FSProjFile.IdLabel).Value);
            var particlesFilePath = elem.Element(FSProjFile.ParticlesFilePathLabel).Value;
            var radius = float.Parse(elem.Element(FSProjFile.ParticleRadiusLabel).Value);
            var density = float.Parse(elem.Element(FSProjFile.DensityLabel).Value);
            var stiffness = float.Parse(elem.Element(FSProjFile.StiffnessLabel).Value);
            var viscosity = float.Parse(elem.Element(FSProjFile.ViscosityLabel).Value);
            var isBoundary = bool.Parse(elem.Element(FSProjFile.IsBoundarylabel).Value);
            var doExportVDB = bool.Parse(elem.Element(FSProjFile.DoExportVDBLabel).Value);
            var exportDirectory = elem.Element(FSProjFile.ExportDirectory).Value;
            var fluidScene = new FluidScene(model.Scenes, parent, model.VDBModel, canvas);
            fluidScene.SetParticlesFromFile(model.VDBModel, model.FileIOModel, canvas, particlesFilePath, radius);
            fluidScene.ParticleRadius = radius;
            fluidScene.Density = density;
            fluidScene.Stiffness = stiffness;
            fluidScene.Viscosity = viscosity;
            fluidScene.Name = name;
            fluidScene.IsBoundary = isBoundary;
            fluidScene.ExportModel.DoExportVDB = doExportVDB;
            fluidScene.ExportModel.VDBExportDirectory = exportDirectory;
            fluidScene.Send();

            canvas.BuildShader(model.Scenes, fluidScene.Id);
            canvas.Render();

            return fluidScene;
        }

        private EmitterScene ReadEmitterScene(MainModel model, Canvas3d canvas, XElement elem, SolverScene parent)
        {
            var name = elem.Attribute(FSProjFile.NameLabel).Value;

            var particlesFilePath = elem.Element(FSProjFile.ParticlesFilePathLabel).Value;
            var radius = float.Parse(elem.Element(FSProjFile.ParticleRadiusLabel).Value);
            var density = float.Parse(elem.Element(FSProjFile.DensityLabel).Value);
            var stiffness = float.Parse(elem.Element(FSProjFile.StiffnessLabel).Value);
            var viscosity = float.Parse(elem.Element(FSProjFile.ViscosityLabel).Value);
//            var isBoundary = bool.Parse(elem.Element(FSProjFile.IsBoundarylabel).Value);
            var doExportVDB = bool.Parse(elem.Element(FSProjFile.DoExportVDBLabel).Value);
            var exportDirectory = elem.Element(FSProjFile.ExportDirectory).Value;
            var startTimeStep = int.Parse(elem.Element(FSProjFile.StartStepLabel).Value);
            var endTimeStep = int.Parse(elem.Element(FSProjFile.EndStepLabel).Value);
            var interval = int.Parse(elem.Element(FSProjFile.IntervalLabel).Value);
            var emitterScene = new EmitterScene(model.Scenes, parent, model.VDBModel, canvas);
            emitterScene.SetParticlesFromFile(model.VDBModel, model.FileIOModel, canvas, particlesFilePath, radius);

            emitterScene.ParticleRadius = radius;
            emitterScene.Density = density;
            emitterScene.Stiffness = stiffness;
            emitterScene.Viscosity = viscosity;
            emitterScene.Name = name;
            emitterScene.StartTimeStep = startTimeStep;
            emitterScene.EndTimeStep = endTimeStep;
            emitterScene.Interval = interval;
            emitterScene.ExportModel.DoExportVDB = doExportVDB;
            emitterScene.ExportModel.VDBExportDirectory = exportDirectory;
            emitterScene.Send();

            canvas.BuildShader(model.Scenes, emitterScene.Id);
            canvas.Render();

            return emitterScene;
        }

        private CSGBoundaryScene ReadCSGBoundaryScene(MainModel model, Canvas3d canvas, XElement elem, SolverScene parent)
        {
            var name = elem.Attribute(FSProjFile.NameLabel).Value;
            var box = ReadBox3d(elem.Element(FSProjFile.Box3dLabel));

            var bScene = new CSGBoundaryScene(parent, model.Scenes);
            bScene.Name = name;
            bScene.BoundingBox = box;
            bScene.Send();
            canvas.BuildShader(model.Scenes, bScene.Id);
            canvas.Render();
            return bScene;
        }

        private Box3d ReadBox3d(XElement elem)
        {
            var min = ReadVector3d(elem.Element("Min"));
            var max = ReadVector3d(elem.Element("Max"));
            return new Box3d(min, max);
        }

        private Vector3d ReadVector3d(XElement elem)
        {
            var x = double.Parse(elem.Element(FSProjFile.XLabel).Value);
            var y = double.Parse(elem.Element(FSProjFile.YLabel).Value);
            var z = double.Parse(elem.Element(FSProjFile.ZLabel).Value);
            return new Vector3d(x, y, z);
        }
    }
}
