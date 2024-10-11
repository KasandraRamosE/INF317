using System;
using System.Collections.Generic;

namespace ClassLibrary1
{
    public class Class1
    {
        public double infija(string expresion)
        {
            Stack<double> val = new Stack<double>();
            Stack<string> ope = new Stack<string>();
            string[] tokens = expresion.Split(' ');

            foreach (string token in tokens)
            {
                double valor;
                if (double.TryParse(token, out valor))
                    val.Push(valor);
                else if (token == "(")
                    ope.Push(token);
                else if (token == ")")
                {
                    while (ope.Peek() != "(")
                        val.Push(operacion(ope.Pop(), val.Pop(), val.Pop()));
                    ope.Pop();
                }
                else if (esoperador(token))
                {
                    while (ope.Count > 0 && orden(token) <= orden(ope.Peek()))
                        val.Push(operacion(ope.Pop(), val.Pop(), val.Pop()));
                    ope.Push(token);
                }
            }

            while (ope.Count > 0)
                val.Push(operacion(ope.Pop(), val.Pop(), val.Pop()));

            return val.Pop();
        }

        public string aposfija(string expresion)
        {
            Stack<string> pila = new Stack<string>();
            string posfija = "";

            string[] tokens = expresion.Split(' ');

            foreach (string token in tokens)
            {
                double valor;
                if (double.TryParse(token, out valor))
                    posfija += token + " ";
                else if (token == "(")
                    pila.Push(token);
                else if (token == ")")
                {
                    while (pila.Peek() != "(")
                        posfija += pila.Pop() + " ";
                    pila.Pop();
                }
                else if (esoperador(token))
                {
                    while (pila.Count > 0 && orden(token) <= orden(pila.Peek()))
                        posfija += pila.Pop() + " ";
                    pila.Push(token);
                }
            }

            while (pila.Count > 0)
                posfija += pila.Pop() + " ";

            return posfija.Trim();
        }

        public string aprefija(string expresion)
        {
            char[] charArray = expresion.ToCharArray();
            Array.Reverse(charArray);
            string exprInvertida = new string(charArray);

            exprInvertida = exprInvertida.Replace('(', '#');
            exprInvertida = exprInvertida.Replace(')', '(');
            exprInvertida = exprInvertida.Replace('#', ')');

            string posfija = aposfija(exprInvertida);
            charArray = posfija.ToCharArray();
            Array.Reverse(charArray);
            return new string(charArray).Trim();
        }

        public double resposfija(string expresion)
        {
            Stack<double> pila = new Stack<double>();
            string[] tokens = expresion.Split(' ');

            foreach (string token in tokens)
            {
                double valor;
                if (double.TryParse(token, out valor))
                {
                    pila.Push(valor);
                }
                else if (esoperador(token))
                {
                    double operand2 = pila.Pop();
                    double operand1 = pila.Pop();
                    pila.Push(operacion(token, operand2, operand1));
                }
            }

            return pila.Pop();
        }

        public double resprefija(string expresion)
        {
            Stack<double> pila = new Stack<double>();
            string[] tokens = expresion.Split(' ');

            for (int i = tokens.Length - 1; i >= 0; i--)
            {
                double valor;
                if (double.TryParse(tokens[i], out valor))
                {
                    pila.Push(valor);
                }
                else if (esoperador(tokens[i]))
                {
                    double op1 = pila.Pop();
                    double op2 = pila.Pop();
                    pila.Push(operacion(tokens[i], op1, op2));
                }
            }

            return pila.Pop();
        }

        private bool esoperador(string token)
        {
            return token == "+" || token == "-" || token == "*" || token == "/";
        }

        private double operacion(string op, double operand2, double operand1)
        {
            switch (op)
            {
                case "+": return operand1 + operand2;
                case "-": return operand1 - operand2;
                case "*": return operand1 * operand2;
                case "/": return operand1 / operand2;
                default: throw new ArgumentException("Operador desconocido: " + op);
            }
        }

        private int orden(string op)
        {
            if (op == "+" || op == "-")
                return 1;
            else if (op == "*" || op == "/")
                return 2;
            else
                return 0;
        }
    }
}
