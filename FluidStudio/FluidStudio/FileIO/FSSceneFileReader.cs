using FluidStudio.Physics;
using PG.Control.OpenGL;
using PG.Scene;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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
            physicsScene.TimeStep = timeStep;
            physicsScene.Create(model.Scenes, fluids, new List<CSGBoundaryScene>(), timeStep, "");
            model.PhysicsModel.Solvers.Add(physicsScene);
        }

        private FluidScene ReadFluidScene(MainModel model, Canvas3d canvas, XElement elem)
        {
//            var id = int.Parse(elem.Element(FSProjFile.IdLabel).Value);
            var particlesFilePath = elem.Element(FSProjFile.ParticlesFilePathLabel).Value;
            var stiffness = float.Parse(elem.Element(FSProjFile.StiffnessLabel).Value);
            var viscosity = float.Parse(elem.Element(FSProjFile.ViscosityLabel).Value);
            var isBoundary = bool.Parse(elem.Element(FSProjFile.IsBoundarylabel).Value);
            var fluidScene = new FluidScene();
            fluidScene.SetParticlesFromFile(model.Scenes, model.VDBModel, canvas, particlesFilePath);
            fluidScene.Create(model.Scenes, 1.0f, stiffness, viscosity, "", isBoundary);

            canvas.BuildShader(model.Scenes, fluidScene.Id);
            canvas.Render();

            return fluidScene;
        }
    }
}
