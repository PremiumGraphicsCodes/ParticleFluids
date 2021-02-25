using FluidStudio.Physics;
using FluidStudio.VDB;
using PG.Scene;

namespace FluidStudio
{
    public class MainModel
    {
        public SceneList Scenes { get; }

        public PhysicsModel PhysicsModel { get; }

        public VDBModel VDBModel { get; }

        public MainModel()
        {
            this.Scenes = new SceneList();
            this.PhysicsModel = new PhysicsModel();
            this.VDBModel = new VDBModel(this.Scenes);
        }
    }
}
