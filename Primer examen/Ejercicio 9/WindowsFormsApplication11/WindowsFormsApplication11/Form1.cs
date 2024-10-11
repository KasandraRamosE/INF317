using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication11
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "Archivos de imagen|*.png;*.jpg;*.jpeg;*.bmp";

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                // cargar la imagen
                pictureBox1.Image = new Bitmap(openFileDialog1.FileName);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image == null)
            {
                MessageBox.Show("Por favor, cargue una imagen primero usando el Botón 1.");
                return;
            }

            // obtener la imagen cargada en pictureBox1
            Bitmap bmp = new Bitmap(pictureBox1.Image);

            // nuevo bitmap para la imagen con detección de bordes
            Bitmap edgeDetectedImage = new Bitmap(bmp.Width, bmp.Height);

            // definir los kernels de Sobel
            int[,] Gx = new int[3, 3] { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
            int[,] Gy = new int[3, 3] { { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } };

            // recorrer cada píxel de la imagen 
            for (int i = 1; i < bmp.Width - 1; i++)
            {
                for (int j = 1; j < bmp.Height - 1; j++)
                {
                    int pixelX = 0; 
                    int pixelY = 0;

                    // aplicar las máscaras de Sobel
                    for (int k = -1; k <= 1; k++)
                    {
                        for (int l = -1; l <= 1; l++)
                        {
                            // obtener el color del píxel en la posición (i+k, j+l)
                            Color c = bmp.GetPixel(i + k, j + l);

                            // convertir a escala de grises
                            int intensidad = (c.R + c.G + c.B) / 3;

                            // aplicar las máscaras Gx y Gy
                            pixelX += Gx[k + 1, l + 1] * intensidad;
                            pixelY += Gy[k + 1, l + 1] * intensidad;
                        }
                    }

                    // calcular la magnitud del gradiente
                    int magnitud = (int)Math.Sqrt((pixelX * pixelX) + (pixelY * pixelY));

                    // limitar los valores de magnitud entre 0 y 255
                    magnitud = Math.Max(0, Math.Min(255, magnitud));

                    // establecer el color resultante en la imagen de destino
                    edgeDetectedImage.SetPixel(i, j, Color.FromArgb(magnitud, magnitud, magnitud));
                }
            }

            pictureBox2.Image = edgeDetectedImage;
        }
    }
}
