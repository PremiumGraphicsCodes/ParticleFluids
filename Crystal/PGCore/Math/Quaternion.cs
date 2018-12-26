namespace PG.Core.Math
{
    public class Quaternion
    {
        private double x;
        private double y;
        private double z;
        private double w;

        public Quaternion(double x, double y, double z, double w)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            this.w = w;
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
    }
}
