using FluidStudio.Physics;
using PG.Scene;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace FluidStudio.FileIO
{
    public class FSProjFileReader
    {
        public void Read(MainModel model, string filePath)
        {
            var elem = XElement.Load(filePath);
            Read(model, elem);
        }

        public void Read(MainModel model, XElement root)
        {
//            var root = elem.Element(FSProjFile.RootLabel);
            var version = root.Attribute(FSProjFile.FileFormatVersionLabel).Value;
            var physicsElem = root.Element(FSProjFile.PhysicsSceneLabel);
            ReadPhysicsScene(model, physicsElem);
        }

        public void ReadPhysicsScene(MainModel model, XElement elem)
        {
            var physicsScene = new SolverScene();
            {
                var name = elem.Element(FSProjFile.NameLabel).Value;
                var id = int.Parse(elem.Element(FSProjFile.IdLabel).Value);
                var particleSystemId = int.Parse(elem.Element(FSProjFile.ParticleSystemIdLabel).Value);
                var stiffness = float.Parse(elem.Element(FSProjFile.StiffnessLabel).Value);
                var viscosity = float.Parse(elem.Element(FSProjFile.ViscosityLabel).Value);
                var fluidScene = new FluidScene();
                fluidScene.Create(model.Scenes, particleSystemId, -1, stiffness, viscosity, "", false);
                physicsScene.Fluids.Add(fluidScene);
            }
            model.PhysicsModel.Scenes.Add(physicsScene);
        }
    }
}
