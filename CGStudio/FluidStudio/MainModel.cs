using FluidStudio.Physics;
using FluidStudio.VDB;

namespace FluidStudio
{
    public class MainModel
    {
        public VDBModel VDBModel { get; }

        public PhysicsSceneList PhysicsModel { get; }

        public MainModel()
        {
            this.VDBModel = new VDBModel();
            this.PhysicsModel = new PhysicsSceneList();
        }
    }
}
