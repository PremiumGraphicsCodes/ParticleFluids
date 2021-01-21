using FluidStudio.Physics;
using FluidStudio.VDB;
using PG.Scene;

namespace FluidStudio
{
    public class MainModel
    {
        public VDBModel VDBModel { get; }

        public PhysicsModel PhysicsModel { get; }

        public SceneList Scenes { get; }

        public MainModel()
        {
            this.VDBModel = new VDBModel();
            this.PhysicsModel = new PhysicsModel();
            this.Scenes = new SceneList();
        }
    }
}
