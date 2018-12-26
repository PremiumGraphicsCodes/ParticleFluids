namespace PGCore.Math
{
    public class Matrix4d
    {
        public Matrix4d() :
            this(
                1,0,0,0,
                0,1,0,0,
                0,0,1,0,
                0,0,0,1
                )
        { }

        public Matrix4d(
            double x00, double x01, double x02, double x03,
            double x10, double x11, double x12, double x13,
            double x20, double x21, double x22, double x23,
            double x30, double x31, double x32, double x33)
        {
            x = new double[4, 4];
            x[0, 0] = x00; x[0, 1] = x01; x[0, 2] = x02; x[0, 3] = x03;
            x[1, 0] = x10; x[1, 1] = x11; x[1, 2] = x12; x[1, 3] = x13;
            x[2, 0] = x20; x[2, 1] = x21; x[2, 2] = x22; x[2, 3] = x23;
            x[3, 0] = x30; x[3, 1] = x31; x[3, 2] = x32; x[3, 3] = x33;
        }

        public double[,] X
        {
            get { return x; }
            set { this.x = value; }
        }

        private double[,] x;
    }
}
