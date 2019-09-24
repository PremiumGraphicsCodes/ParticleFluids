namespace PG.Core.Math
{
    public interface ICurveUVW
    {
        Vector3d GetPosition(double r, double u, double v);
    }
}
