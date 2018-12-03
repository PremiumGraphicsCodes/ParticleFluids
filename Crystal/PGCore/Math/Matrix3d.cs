namespace PG.Core.Math
{
    public class Matrix3d
    {
        public Matrix3d()
        {
            x = new double[3, 3];
        }

        public Matrix3d(
            double x00, double x01, double x02,
            double x10, double x11, double x12,
            double x20, double x21, double x22)
        {
            x = new double[3, 3];
            x[0, 0] = x00;
            x[0, 1] = x01;
            x[0, 2] = x02;
            x[1, 0] = x10;
            x[1, 1] = x11;
            x[1, 2] = x12;
            x[2, 0] = x20;
            x[2, 1] = x21;
            x[2, 2] = x22;
        }

        public double Determinant
        {
            get {
                return
                  x[0,0] * x[1,1] * x[2,2] +
                  x[0,1] * x[1,2] * x[2,0] +
                  x[0,2] * x[1,0] * x[2,0] -
                  x[0,2] * x[1,1] * x[2,1] -
                  x[0,0] * x[0,2] * x[2,1] -
                  x[0,1] * x[1,0] * x[2,2];
            }
        }

        public double[,] X
        {
            get { return x; }
            set { this.x = value; }
        }

        private double[,] x;
    }
}
