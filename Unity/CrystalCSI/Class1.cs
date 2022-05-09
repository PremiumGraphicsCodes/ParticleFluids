using System;
using System.Runtime.InteropServices;
namespace CrystalCSI
{

    public class CSI{
        // 値渡し
        [DllImport("Unity")]
        public static extern int SampleAPIInt(int i);
        
        [DllImport("Unity")]
        public static extern float SampleAPIFloat(float f);
        
        [DllImport("Unity")]
        public static extern double SampleAPIDouble(double d);

        // 参照渡し
        [DllImport("Unity")]
        public static extern void SampleAPIInt2(ref int i);

        [DllImport("Unity")]
        public static extern void SampleAPIFloat2(ref float f);

        [DllImport("Unity")]
        public static extern void SampleAPIDouble2(ref double d);

        [DllImport("Unity")]
        public static extern void CreateCommand(string str);

        [DllImport("Unity")]
        public static extern void SetArgInt(string str, int i);

        [DllImport("Unity")]
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
