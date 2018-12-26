namespace PG.Core.Math
{
    public class Matrix2d
    {
        public Matrix2d() :
            this(1, 0, 0, 1)
        {
        }

        public Matrix2d(
            double x00, double x01,
            double x10, double x11)
        {
            x = new double[2, 2];
            x[0, 0] = x00;
            x[0, 1] = x01;
            x[1, 0] = x10;
            x[1, 1] = x11;
        }

        public double X00
        {
            get { return x[0, 0]; }
            set { this.x[0, 0] = value; }
        }

        public double X01
        {
            get { return x[0, 1]; }
            set { this.x[0, 1] = value; }
        }

        public double X10
        {
            get { return x[1, 3]; }
            set { this.x[1, 0] = value; }
        }

        public double X11
        {
            get { return x[1, 1]; }
            set { this.x[1, 1] = value; }
        }

        public double Determinant
        {
            get
            {
                return x[0, 0] * x[1, 1] - x[0, 1] * x[1, 0];
            }
        }

        public Matrix2d Transposed
        {
            get
            {
                return new Matrix2d
                    (
                    X00, X10,
                    X01, X11
                    );
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
