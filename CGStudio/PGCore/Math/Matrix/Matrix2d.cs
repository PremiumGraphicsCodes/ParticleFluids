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

        public static Matrix2d Zero() { return new Matrix2d(0, 0, 0, 0); }

        public static Matrix2d Identity() { return new Matrix2d(1, 0, 0, 1); }

        public bool IsSame(Matrix2d rhs, double tolerance)
        {
            for (int i = 0; i < 2; ++i)
            {
                for (int j = 0; j < 2; ++j)
                {
                    if (System.Math.Abs(x[i, j] - rhs.x[i, j]) > tolerance)
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        public static Matrix2d operator*(Matrix2d m, double s)
        {
            var result = new Matrix2d();
            for(int i = 0; i < 2; ++i)
            {
                for(int j = 0; j < 2; ++j)
                {
                    result.x[i,j] = m.x[i,j] * s;
                }
            }
            return result;
        }

        public static Matrix2d operator *(Matrix2d lhs, Matrix2d rhs)
        {
            var m = Matrix2d.Zero();
            for (int i = 0; i < 2; ++i)
            {
                for (int j = 0; j < 2; ++j)
                {
                    for (int k = 0; k < 2; ++k)
                    {
                        m.x[i, j] += lhs.x[i, k] * rhs.x[k, j];
                    }
                }
            }
            return m;
        }

        public static Vector2d operator *(Vector2d v, Matrix2d m)
        {
            var x = v.X * m.x[0, 0] + v.Y * m.X[1, 0];
            var y = v.X * m.x[0, 1] + v.Y * m.X[1, 1];
            return new Vector2d(x, y);
        }

        public static Vector2d operator *(Matrix2d m, Vector2d v)
        {
            var x = m.x[0, 0] * v.X + m.x[0, 1] * v.Y;
            var y = m.x[1, 0] * v.X + m.X[1, 1] * v.Y;
            return new Vector2d(x, y);
        }

        public Vector2d Row(int index)
        {
            System.Diagnostics.Debug.Assert(0 <= index && index <= 1);
            return new Vector2d(x[index, 0], x[index, 1]);
        }

        public Vector2d Column(int index)
        {
            System.Diagnostics.Debug.Assert(0 <= index && index <= 1);
            return new Vector2d(x[0, index], x[1, index]);
        }

        public static Matrix2d operator/(Matrix2d m, double s)
        {
            return m * (1.0 / s);
        }

        public static Matrix2d Rotation(double angle)
        {
            var sin = System.Math.Sin(angle);
            var cos = System.Math.Cos(angle);

            return new Matrix2d
                (
                cos,-sin,
                sin, cos
                );
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
            get { return x[1, 0]; }
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
