namespace PG.Core.Math
{
    public interface IVolume3d
    {
        Vector3d GetPosition(double r, double u, double v);

        bool IsInside(Vector3d position);
    }
}
