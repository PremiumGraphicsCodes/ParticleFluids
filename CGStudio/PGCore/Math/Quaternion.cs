namespace PG.Core.Math
{
    public class Quaternion
    {
        private double x;
        private double y;
        private double z;
        private double w;

        public Quaternion()
        {
            this.x = 0.0;
            this.y = 0.0;
            this.z = 0.0;
            this.w = 0.0;
        }

        public Quaternion(double x, double y, double z, double w)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            this.w = w;
        }

        public Quaternion(Vector3d axis, double angle)
        {
            var s = System.Math.Sin(angle);
            w = System.Math.Cos(angle);
            x = axis.X * s;
            y = axis.Y * s;
            z = axis.Z * s;
        }

        public bool IsSame(Quaternion rhs, double tolerance)
        {
            return
                System.Math.Abs(this.x - rhs.x) < tolerance &&
                System.Math.Abs(this.y - rhs.y) < tolerance &&
                System.Math.Abs(this.z - rhs.z) < tolerance &&
                System.Math.Abs(this.w - rhs.w) < tolerance;
        }

        public Matrix3d ToRotationMatrix()
        {
            var m11 = 1.0 - 2.0 * y * y - 2.0 * z * z;
            var m12 = 2.0 * x * y + 2.0 * w * z;
            var m13 = 2.0 * x * z - 2.0 * w * y;

            var m21 = 2.0 * x * y - 2.0 * w * z;
            var m22 = 1.0 - 2.0 * x * x - 2.0 * z * z;
            var m23 = 2.0 * y * z + 2.0 * w * x;

            var m31 = 2.0 * x * z + 2.0 * w * y;
            var m32 = 2.0 * y * z - 2.0 * w * x;
            var m33 = 1.0 - 2.0 * x * x - 2.0 * y * y;
            return new Matrix3d
                (
                m11, m12, m13,
                m21, m22, m23,
                m31, m32, m33
                );
        }

        public void FromRotationMatrix(Matrix3d m)
        {
            // 最大成分を検索
            var elem = new double[4]; // 0:x, 1:y, 2:z, 3:w
            elem[0] = m.X00 - m.X11 - m.X22 + 1.0;
            elem[1] = -m.X00 + m.X11 - m.X22 + 1.0f;
            elem[2] = -m.X00 - m.X11 + m.X22 + 1.0f;
            elem[3] = m.X00 + m.X11 + m.X22 + 1.0f;

            int biggestIndex = 0;
            for (int i = 1; i < 4; i++)
            {
                if (elem[i] > elem[biggestIndex])
                {
                    biggestIndex = i;
                }
            }

            if (elem[biggestIndex] < 0.0f) {
                return; // 引数の行列に間違いあり！
            }

            // 最大要素の値を算出
            var v = System.Math.Sqrt(elem[biggestIndex]) * 0.5;
            var mult = 0.25f / v;

            switch (biggestIndex)
            {
                case 0: // x
                    x = v;
                    y = (m.X01 + m.X10) * mult;
                    z = (m.X20 + m.X02) * mult;
                    w = (m.X12 - m.X21) * mult;
                    break;
                case 1: // y
                    y = v;
                    x = (m.X10 + m.X10) * mult;
                    z = (m.X12 + m.X21) * mult;
                    w = (m.X20 - m.X02) * mult;
                    break;
                case 2: // z
                    x = (m.X20 + m.X02) * mult;
                    y = (m.X12 + m.X21) * mult;
                    z = v;
                    w = (m.X01 - m.X10) * mult;
                    break;
                case 3: // w
                    x = (m.X12 - m.X21) * mult;
                    y = (m.X20 - m.X02) * mult;
                    z = (m.X01 - m.X10) * mult;
                    w = v;
                    break;
            }
        }

        public double Norm
        {
            get { return System.Math.Sqrt( x*x + y*y + z*z + w*w ); }
        }

        public Quaternion Normalized()
        {
            var n = Norm;
            return new Quaternion(x / n, y / n, z / n, w / n);
        }

        public double Dot(Quaternion rhs)
        {
            return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
        }

        public static Quaternion operator-(Quaternion rhs)
        {
            return new Quaternion(-rhs.x, -rhs.y, -rhs.z, -rhs.w);
        }

        public static Quaternion operator+(Quaternion lhs, Quaternion rhs)
        {
            return new Quaternion(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
        }

        public static Quaternion operator-(Quaternion lhs, Quaternion rhs)
        {
            return new Quaternion(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
        }

        public static Quaternion operator*(double lhs, Quaternion rhs)
        {
            return new Quaternion(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
        }

        public Quaternion Slerp(Quaternion lhs, Quaternion rhs, double t)
        {
            // Only unit quaternions are valid rotations.
            // Normalize to avoid undefined behavior.
            var v0 = lhs.Normalized();
            var v1 = rhs.Normalized();

            // Compute the cosine of the angle between the two vectors.
            var dot = v0.Dot(v1);

            // If the dot product is negative, slerp won't take
            // the shorter path. Note that v1 and -v1 are equivalent when
            // the negation is applied to all four components. Fix by 
            // reversing one quaternion.
            if (dot < 0.0f)
            {
                v1 = -v1;
                dot = -dot;
            }

            const double DOT_THRESHOLD = 0.9995;
            if (dot > DOT_THRESHOLD)
            {
                // If the inputs are too close for comfort, linearly interpolate
                // and normalize the result.

                Quaternion result = v0 + t * (v1 - v0);
                result = result.Normalized();
                return result;
            }

            // Since dot is in range [0, DOT_THRESHOLD], acos is safe
            double theta_0 = System.Math.Acos(dot);        // theta_0 = angle between input vectors
            double theta = theta_0 * t;          // theta = angle between v0 and result
            double sin_theta = System.Math.Sin(theta);     // compute this value only once
            double sin_theta_0 = System.Math.Sin(theta_0); // compute this value only once

            double s0 = System.Math.Cos(theta) - dot * sin_theta / sin_theta_0;  // == sin(theta_0 - theta) / sin(theta_0)
            double s1 = sin_theta / sin_theta_0;

            return (s0 * v0) + (s1 * v1);
        }
    }
}
