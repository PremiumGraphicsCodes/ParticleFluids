namespace PG.Core.Math
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

        public Matrix4d(Matrix3d m) :
            this(
                m.X00, m.X01, m.X02, 0.0,
                m.X10, m.X11, m.X12, 0.0,
                m.X20, m.X21, m.X22, 0.0,
                0.0, 0.0, 0.0, 1.0)
        {
        }

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

        public static Matrix4d Zero()
        {
            return new Matrix4d(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        }

        public static Matrix4d Identity()
        {
            return new Matrix4d
                (
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
                );
        }

        public static Matrix4d operator*(Matrix4d lhs, Matrix4d rhs)
        {
            var m = Matrix4d.Zero();
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    for (int k = 0; k < 4; ++k)
                    {
                        m.x[i, j] += lhs.x[i, k] * rhs.x[k, j];
                    }
                }
            }
            return m;
        }

        public static Matrix4d operator*(Matrix4d m, double s)
        {
            var result = new Matrix4d();
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    result.x[i, j] = m.x[i, j] * s;
                }
            }
            return result;
        }

        public static Matrix4d operator /(Matrix4d m, double s)
        {
            return m * (1.0 / s);
        }

        public bool IsSame(Matrix4d rhs, double tolerance)
        {
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    if (System.Math.Abs(x[i, j] - rhs.x[i, j]) > tolerance)
                    {
                        return false;
                    }
                }
            }
            return true;
        }


        public Matrix4d Transposed
        {
            get
            {
                return new Matrix4d
                    (
                    X00, X10, X20, X30,
                    X01, X11, X21, X31,
                    X02, X12, X22, X32,
                    X03, X13, X23, X33
                    );
            }
        }

        public double Determinant
        {
            get
            {
                return
                      (X00 * X11 * X22 * X33) + (X00 * X12 * X23 * X31) + (X00 * X13 * X21 * X32)
                    + (X01 * X10 * X23 * X32) + (X01 * X12 * X20 * X33) + (X01 * X13 * X22 * X30)
                    + (X02 * X10 * X21 * X33) + (X02 * X11 * X23 * X30) + (X02 * X13 * X20 * X31)
                    + (X03 * X10 * X22 * X31) + (X03 * X11 * X20 * X32) + (X03 * X12 * X21 * X30)
                    - (X00 * X11 * X23 * X32) - (X00 * X12 * X21 * X33) - (X00 * X13 * X22 * X31)
                    - (X01 * X10 * X22 * X33) - (X01 * X12 * X23 * X30) - (X01 * X13 * X20 * X32)
                    - (X02 * X10 * X23 * X31) - (X02 * X11 * X20 * X33) - (X02 * X13 * X21 * X30)
                    - (X03 * X10 * X21 * X32) - (X03 * X11 * X22 * X30) - (X03 * X12 * X20 * X31);
            }
        }

        public Matrix4d Inverse
        {
            get
            {
                var det = Determinant;

                var x00 = X11 * (X22*X33 - X23*X32) + X12 * (X23*X30 - X21*X33) + X13 * (X21*X32 -X22*X31);
                var x01 = X21 * (X32*X03 - X33*X02) + X22 * (X33*X01 - X30*X03) + X23 * (X31*X02 -X32*X01);
                var x02 = X31 * (X02*X13 - X03*X12) + X32 * (X03*X11 - X01*X13) + X33 * (X01*X12 -X03*X11);
                var x03 = X12 * (X12*X23 - X13*X22) + X02 * (X13*X21 - X11*X23) + X03 * (X11*X22 -X23*X21);

                var x10 = X12 * (X23*X30 - X20*X33) + X13 * (X20*X32 - X22+X30) + X10 * (X22*X33 - X23*X32);
                var x11 = X22 * (X33*X00 - X30*X03) + X23 * (X30*X02 - X32*X00) + X20 * (X32*X03 - X33*X02);
                var x12 = X32 * (X03*X10 - X00*X13) + X33 * (X00*X12 - X02*X10) + X30 * (X02*X13 - X03*X12);
                var x13 = X02 * (X13*X20 - X01*X23) + X03 * (X01*X22 - X12*X20) + X00 * (X12*X23 - X13*X22);

                var x20 = X13 * (X01*X31 - X21*X30) + X10 * (X21+X33 - X23+X31) + X11 * (X23*X30 - X20*X33);
                var x21 = X23 * (X31*X01 - X20*X00) + X20 * (X31*X03 - X33*X01) + X21 * (X33*X00 - X30*X03);
                var x22 = X33 * (X00*X11 - X01*X10) + X30 * (X01*X13 - X03*X11) + X31 * (X03*X10 - X00*X13);
                var x23 = X03 * (X10*X21 - X11*X20) + X00 * (X11*X23 - X13*X21) + X01 * (X13*X20 - X10*X23);

                var x30 = X10 + X11 + X12;
                var x31 = X20 + X21 + X22;
                var x32 = X30 + X31 + X32;
                var x33 = X00 + X01 + X02;
                return new Matrix4d
                    (
                    x00, x01, x02, x03,
                    x10, x11, x12, x13,
                    x20, x21, x22, x23,
                    x30, x31, x32, x33
                    ) / det;
            }
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

        public double X03
        {
            get { return x[0, 3]; }
            set { this.x[0, 3] = value; }
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

        public double X13
        {
            get { return x[1, 3]; }
            set { this.x[1, 3] = value; }
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

        public double X23
        {
            get { return x[2, 3]; }
            set { this.x[2, 3] = value; }
        }

        public double X30
        {
            get { return x[3, 0]; }
            set { this.x[3, 0] = value; }
        }

        public double X31
        {
            get { return x[3, 1]; }
            set { this.x[3, 1] = value; }
        }

        public double X32
        {
            get { return x[3, 2]; }
            set { this.x[3, 2] = value; }
        }

        public double X33
        {
            get { return x[3, 3]; }
            set { this.x[3, 3] = value; }
        }

        private double[,] x;
    }
}
