using FluidStudio.VDB;
using PG.Control.OpenGL;
using PG.Scene;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CreateLabels = PG.MeshBoundarySceneCreateLabels;
using UpdateLabels = PG.MeshBoundarySceneUpdateLabels;

namespace FluidStudio.Physics.MeshBoundary
{
    public class MeshBoundaryScene : IPhysicsScene
    {
        public string Name { get; private set; }

        public int Id { get { return id; } }

        private int id;

        private int meshId;

        public string MeshFilePath { get; set; }

        public MeshBoundaryScene()
        {

        }

        public MeshBoundaryScene(SceneList world, string name, int meshId)
        {
            Create(world, name, meshId);
        }

        public void Create(SceneList world, string name, int meshId)
        {
            var command = new PG.CLI.PhysicsCommand(CreateLabels.CommandNameLabel);
            command.Execute(world.Adapter);
            this.id = command.GetResult<int>(CreateLabels.NewIdLabel);
            this.Name = name;
            this.meshId = meshId;
            Update(world, name, meshId);
        }

        public void Update(SceneList world, string name, int meshId)
        {
            var command = new PG.CLI.PhysicsCommand(UpdateLabels.CommandNameLabel);
            command.SetArg(UpdateLabels.IdLabel, id);
            command.SetArg(UpdateLabels.NameLabel, name);
            command.SetArg(UpdateLabels.MeshIdLabel, meshId);
            command.Execute(world.Adapter);
            this.Name = name;
        }

        public void SetMeshFromFile(SceneList world, VDBModel vdb, Canvas3d canvas, string meshFilePath)
        {
            // TODO 前のPSのクリア処理．
            var id = vdb.ReadOBJ(world, meshFilePath);
            if(id > 0)
            {
                this.meshId = id;
                canvas.BuildShader(world, meshId);
                canvas.Render();
                this.MeshFilePath = meshFilePath;
            }
        }

    }
}
