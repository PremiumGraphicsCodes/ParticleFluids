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

        public static Matrix3d Zero()
        {
            return new Matrix3d(0, 0, 0, 0, 0, 0, 0, 0, 0);
        }

        public static Matrix3d Identity()
        {
            return new Matrix3d(1, 0, 0, 0, 1, 0, 0, 0, 1);
        }

        public bool IsSame(Matrix3d rhs, double tolerance)
        {
            for(int i = 0; i < 3; ++i)
            {
                for(int j = 0; j < 3; ++j)
                {
                    if( System.Math.Abs( x[i,j] - rhs.x[i,j]) > tolerance)
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        public static Matrix3d operator*(Matrix3d m, double s)
        {
            var result = new Matrix3d();
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    result.x[i, j] = m.x[i, j] * s;
                }
            }
            return result;
        }

        public static Matrix3d operator*(Matrix3d lhs, Matrix3d rhs)
        {
            var m = Matrix3d.Zero();
            for(int i = 0; i < 3; ++i)
            {
                for(int j = 0; j < 3; ++j)
                {
                    for (int k = 0; k < 3; ++k)
                    {
                        m.x[i, j] += lhs.x[i, k] * rhs.x[k, j];
                    }
                }
            }
            return m;
        }

        public static Matrix3d operator/(Matrix3d m, double s)
        {
            return m * (1.0 / s);
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
            get { return x[1, 0]; }
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

        public Matrix3d Inverse
        {
            get
            {
                var det = Determinant;
                var x00 = X11 * X22 - X12 * X21;
                var x01 = X21 * X02 - X22 * X01;
                var x02 = X01 * X12 - X02 * X11;
                var x10 = X12 * X20 - X10 * X22;
                var x11 = X22 * X00 - X10 * X02;
                var x12 = X02 * X10 - X00 * X12;
                var x20 = X01 * X21 - X11 * X20;
                var x21 = X20 * X01 - X21 * X00;
                var x22 = X00 * X11 - X01 * x10;
                return new Matrix3d(x00, x01, x02, x10, x11, x12, x20, x21, x22) / det;
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
