namespace FluidStudio.Physics
{
    public interface IPhysicsScene
    {
        IPhysicsScene Parent { get; }

        int Id { get; }

        string Name { get; }
    }
}
