using System;
using System.Runtime.InteropServices;
namespace CrystalCSI
{

    public class CSI{

        [DllImport("CrystalCI")]
        public static extern void CreateCommand(string str);

        [DllImport("CrystalCI")]
        public static extern void SetArgInt(string str, int i);

        [DllImport("CrystalCI")]
        public static extern void Execute();



        /*
    // 配列の参照渡し
    [DllImport("NativePluginSample")]
    public static extern void SampleAPIIntArray(int[] intArray, int intArraySize);
    [DllImport("NativePluginSample")]
    public static extern void SampleAPILongArray(int[] longArray, int longArraySize);
    [DllImport("NativePluginSample")]
    public static extern void SampleAPIFloatArray(float[] floatArray, int floatArraySize);
    [DllImport("NativePluginSample")]
    public static extern void SampleAPIDoubleArray(double[] doubleArray, int doubleArraySize);

    // 文字列
    [DllImport("NativePluginSample")]
    public static extern string SampleAPIString1();
    [DllImport("NativePluginSample")]
    public static extern string SampleAPIString2(string str);
    */
    }
}
