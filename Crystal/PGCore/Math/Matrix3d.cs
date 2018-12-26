namespace PG.Core.Math
{
    public class Matrix3d
    {
        public Matrix3d() :
            this(1,0,0,0,1,0,0,0,1)
        {
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

        public double X02
        {
            get { return x[0, 2]; }
            set { this.x[0, 2] = value; }
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

        public double X12
        {
            get { return x[1, 2]; }
            set { this.x[1, 2] = value; }
        }

        public double X20
        {
            get { return x[2, 0]; }
            set { this.x[2, 0] = value; }
        }

        public double X21
        {
            get { return x[2, 1]; }
            set { this.x[2, 1] = value; }
        }

        public double X22
        {
            get { return x[2, 2]; }
            set { this.x[2, 2] = value; }
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

        public Matrix3d Transposed
        {
            get
            {
                return new Matrix3d
                    (
                    X00, X10, X20,
                    X01, X11, X21,
                    X02, X12, X22
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
