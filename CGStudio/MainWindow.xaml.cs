using System;
using System.Windows;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;

namespace CGStudio
{
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {
        /// <summary>
        /// コンストラクタ
        /// </summary>
        public MainWindow()
        {
            InitializeComponent();
        }

        /// <summary>
        /// glControlの起動時に実行される。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void glControl_Load(object sender, EventArgs e)
        {
            GL.ClearColor(Color4.Black);
            GL.Enable(EnableCap.DepthTest);
        }

        /// <summary>
        /// glControlのサイズ変更時に実行される。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void glControl_Resize(object sender, EventArgs e)
        {
            GL.Viewport(0, 0, glControl.Size.Width, glControl.Size.Height);
            GL.LoadIdentity();
            // 平行投影
            GL.Ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
        }

        /// <summary>
        /// glControlの描画時に実行される。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void glControl_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
        {
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            GL.Color4(Color4.White);
            GL.Begin(BeginMode.Polygon);
            GL.Vertex3(0.5, 0.5, 0.0);
            GL.Vertex3(-0.5, 0.5, 0.0);
            GL.Vertex3(-0.5, -0.5, 0.0);
            GL.Vertex3(0.5, -0.5, 0.0);
            GL.End();

            glControl.SwapBuffers();
        }
    }
}
