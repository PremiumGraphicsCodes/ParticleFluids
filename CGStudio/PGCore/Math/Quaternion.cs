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
            var s = System.Math.Sin(angle * 0.5);
            w = System.Math.Cos(angle * 0.5);
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
            var x = -this.x;
            var y = -this.y;
            var z = -this.z;

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

        public static Quaternion FromRotationMatrix(Matrix3d mat)
        {
            Quaternion q = new Quaternion();

            double s;
            double tr = mat.X00 + mat.X11 + mat.X22 + 1.0f;
            if (tr >= 1.0f)
            {
                s = 0.5f / System.Math.Sqrt(tr);
                q.w = 0.25f / s;
                q.x = (mat.X12 - mat.X21) * s;
                q.y = (mat.X20 - mat.X02) * s;
                q.z = (mat.X01 - mat.X10) * s;
                return q;
            }
            else
            {
                double max;
                if (mat.X11 > mat.X22)
                {
                    max = mat.X11;
                }
                else
                {
                    max = mat.X22;
                }

                if (max < mat.X00)
                {
                    s = System.Math.Sqrt(mat.X00 - (mat.X11 + mat.X22) + 1.0f);
                    double x = s * 0.5;
                    s = 0.5f / s;
                    q.x = x;
                    q.y = (mat.X01 + mat.X10) * s;
                    q.z = (mat.X20 + mat.X02) * s;
                    q.w = (mat.X12 - mat.X21) * s;
                    return q;
                }
                else if (max == mat.X11)
                {
                    s = System.Math.Sqrt(mat.X11 - (mat.X22 + mat.X00) + 1.0f);
                    double y = s * 0.5;
                    s = 0.5f / s;
                    q.x = (mat.X01 + mat.X10) * s;
                    q.y = y;
                    q.z = (mat.X12 + mat.X21) * s;
                    q.w = (mat.X20 - mat.X02) * s;
                    return q;
                }
                else
                {
                    s = System.Math.Sqrt(mat.X22 - (mat.X00 + mat.X11) + 1.0f);
                    double z = s * 0.5;
                    s = 0.5f / s;
                    q.x = (mat.X20 + mat.X02) * s;
                    q.y = (mat.X12 + mat.X21) * s;
                    q.z = z;
                    q.w = (mat.X01 - mat.X10) * s;
                    return q;
                }
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
