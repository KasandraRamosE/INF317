using System;
using System.Windows.Forms;
using ClassLibrary1;

namespace Ejercicio7calculadora
{
    public partial class Form1 : Form
    {
        private string expresion = "";
        private Class1 c1 = new Class1();

        public Form1()
        {
            InitializeComponent();
        }

        private void button_Click(object sender, EventArgs e)
        {
            Button btn = (Button)sender;
            expresion += btn.Text;
            textBox1.Text = expresion;
        }

        private void button11_Click(object sender, EventArgs e)
        {
            try
            {
                string fexpresion = separar(expresion);
                double res = c1.infija(fexpresion);
                textBox1.Text = res.ToString();
            }
            catch (Exception ex)
            {
                textBox1.Text = "Error: " + ex.Message;
            }
        }

        private void button16_Click(object sender, EventArgs e)
        {
            expresion = "";
            textBox1.Clear();
        }

        private string separar(string expr)
        {
            string aux = "";
            foreach (char c in expr)
            {
                if (esoperador(c) || c == '(' || c == ')')
                    aux += " " + c + " ";
                else
                    aux += c;
            }
            return aux.Trim();
        }

        private bool esoperador(char c)
        {
            return c == '+' || c == '-' || c == '*' || c == '/';
        }

        private void button19_Click(object sender, EventArgs e)
        {
            try
            {
                string fexpresion = separar(expresion);
                string eposfija = c1.aposfija(fexpresion);
                double res = c1.resposfija(eposfija);
                textBox1.Text = res.ToString();
            }
            catch (Exception ex)
            {
                textBox1.Text = "Error: " + ex.Message;
            }
        }

        private void button20_Click(object sender, EventArgs e)
        {
            try
            {
                string fexpresion = separar(expresion);
                string eprefija = c1.aprefija(fexpresion);
                double res = c1.resprefija(eprefija);
                textBox1.Text = res.ToString();
            }
            catch (Exception ex)
            {
                textBox1.Text = "Error: " + ex.Message;
            }
        }
    }
}
