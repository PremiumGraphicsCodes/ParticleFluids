using FluidStudio.Physics;
using PG.Control.OpenGL;
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
            var physicsScene = new SolverScene();
            var effectLength = float.Parse(elem.Element(FSProjFile.EffectLengthLabel).Value);
            var timeStep = float.Parse(elem.Element(FSProjFile.TimeStepLabel).Value);
            var scenes = elem.Elements(FSProjFile.FluidSceneLabel);
            var fluids = new List<FluidScene>();
            foreach(var scene in scenes)
            {
                var fluid = ReadFluidScene(model, canvas, scene);
                fluids.Add(fluid);
//                physicsScene.Fluids.Add(fluid);
            }
            /*
            {
//                var name = elem.Element(FSProjFile.NameLabel).Value;
                physicsScene.Fluids.Add(fluidScene);
            }
            */
            var name = elem.Attribute(FSProjFile.NameLabel).Value;
            physicsScene.TimeStep = timeStep;
            physicsScene.Create(model.Scenes, fluids, effectLength, timeStep, name);
            model.PhysicsModel.Solvers.Add(physicsScene);
        }

        private FluidScene ReadFluidScene(MainModel model, Canvas3d canvas, XElement elem)
        {
            var name = elem.Attribute(FSProjFile.NameLabel).Value;
//            var id = int.Parse(elem.Element(FSProjFile.IdLabel).Value);
            var particlesFilePath = elem.Element(FSProjFile.ParticlesFilePathLabel).Value;
            var density = float.Parse(elem.Element(FSProjFile.DensityLabel).Value);
            var stiffness = float.Parse(elem.Element(FSProjFile.StiffnessLabel).Value);
            var viscosity = float.Parse(elem.Element(FSProjFile.ViscosityLabel).Value);
            var isBoundary = bool.Parse(elem.Element(FSProjFile.IsBoundarylabel).Value);
            var doExportVDB = bool.Parse(elem.Element(FSProjFile.DoExportVDBLabel).Value);
            var exportDirectory = elem.Element(FSProjFile.ExportDirectory).Value;
            var fluidScene = new FluidScene();
            fluidScene.SetParticlesFromFile(model.Scenes, model.VDBModel, canvas, particlesFilePath);
            fluidScene.Create(model.Scenes, model.VDBModel, canvas, density, stiffness, viscosity, name, isBoundary);
            fluidScene.ExportModel.DoExportVDB = doExportVDB;
            fluidScene.ExportModel.VDBExportDirectory = exportDirectory;

            canvas.BuildShader(model.Scenes, fluidScene.Id);
            canvas.Render();

            return fluidScene;
        }
    }
}
