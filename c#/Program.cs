using System;
using System.Collections.Generic;
using System.Linq;

namespace aaied2
{
    class Program
    {
        public static int lenY = 20;
        public static int lenX = 20;
        public static List<Campo> campos = new List<Campo>();
        public static int contador = 0;

        static void Main(string[] args)
        {
            MontarCampos();
            ExibirCampos();
            RealizarContagem();
            ExibirContador();
        }
        public static void MontarCampos()
        {
            for (int i = 0; i < lenY; i++)
            {
                for (int j = 0; j < lenX; j++)
                {
                    var campo = new Campo();
                    campo.Montar(i, j);
                    campos.Add(campo);
                }
            }
        }
        public static void ExibirCampos()
        {
            for (int i = 0; i < lenY; i++)
            {
                for (int j = 0; j < lenX; j++)
                {
                    var campo = campos.FirstOrDefault(x => x.X == i && x.Y == j);
                    Console.Write(campo.Indicador);
                }
                Console.WriteLine();
            }
        }

        public static void ExibirContador()
        {
            Console.WriteLine("Total: " + contador);
        }
        public static void RealizarContagem()
        {
            for (int i = 0; i < lenY; i++)
            {
                for (int j = 0; j < lenX; j++)
                {
                    var campo = campos.FirstOrDefault(x => x.X == i && x.Y == j);
                    ValidarGrupo(campo);
                }
            }
        }

        public static void ValidarGrupo(Campo campo)
        {
            if (campo.Indicador == 1)
            {
                int auxValor = 0, auxValidador = 0;

                // validar parte acima
                auxValidador = ValidarAcima(campo);
                auxValor = auxValidador == 0 ? auxValor : auxValidador;
                // validar posterior
                auxValidador = ValidarPosterior(campo);
                auxValor = auxValidador == 0 ? auxValor : auxValidador;
                // validar anterior
                auxValidador = ValidarAnterior(campo);
                auxValor = auxValidador == 0 ? auxValor : auxValidador;
                // validar campos abaixo
                auxValidador = ValidarAbaixo(campo);
                auxValor = auxValidador == 0 ? auxValor : auxValidador;

                campo.Valor = auxValor == 0 ? ++contador : auxValor;
            }
        }

        public static int ValidarAcima(Campo campo)
        {
            var yAcima = campo.Y - 1;
            var xAnterior = campo.X - 1;
            var xLocal = campo.X;
            var xPosterior = campo.X + 1;

            if (yAcima >= 0 && yAcima < lenX)
            {
                if (xAnterior >= 0 && xAnterior < lenY)
                {
                    var campoAtual = campos.FirstOrDefault(x => x.Y == yAcima && x.X == xAnterior);
                    if (campoAtual.ValidarCampoValor())
                    {
                        return campoAtual.Valor;
                    }
                }
                if (xLocal >= 0 && xLocal < lenY)
                {
                    var campoAtual = campos.FirstOrDefault(x => x.Y == yAcima && x.X == xLocal);
                    if (campoAtual.ValidarCampoValor())
                    {
                        return campoAtual.Valor;
                    }
                }
                if (xPosterior >= 0 && xPosterior < lenY)
                {
                    var campoAtual = campos.FirstOrDefault(x => x.Y == yAcima && x.X == xPosterior);
                    if (campoAtual.ValidarCampoValor())
                    {
                        return campoAtual.Valor;
                    }
                }
            }

            return 0;
        }
        public static int ValidarPosterior(Campo campo)
        {
            var yAtual = campo.Y;
            var xPosterior = campo.X + 1;

            if (yAtual >= 0 && yAtual < lenX)
            {
                if (xPosterior >= 0 && xPosterior < lenY)
                {
                    var campoAtual = campos.FirstOrDefault(x => x.Y == yAtual && x.X == xPosterior);
                    if (campoAtual.ValidarCampoValor())
                    {
                        return campoAtual.Valor;
                    }
                }
            }

            return 0;
        }
        public static int ValidarAnterior(Campo campo)
        {
            var yAtual = campo.Y;
            var xAnterior = campo.X - 1;

            if (yAtual >= 0 && yAtual < lenX)
            {
                if (xAnterior >= 0 && xAnterior < lenY)
                {
                    var campoAtual = campos.FirstOrDefault(x => x.Y == yAtual && x.X == xAnterior);
                    if (campoAtual.ValidarCampoValor())
                    {
                        return campoAtual.Valor;
                    }
                }
            }

            return 0;
        }
        public static int ValidarAbaixo(Campo campo)
        {
            var yAbaixo = campo.Y + 1;
            var xAnterior = campo.X - 1;
            var xLocal = campo.X;
            var xPosterior = campo.X + 1;

            if (yAbaixo >= 0 && yAbaixo < lenX)
            {
                if (xAnterior >= 0 && xAnterior < lenY)
                {
                    var campoAtual = campos.FirstOrDefault(x => x.Y == yAbaixo && x.X == xAnterior);
                    if (campoAtual.ValidarCampoValor())
                    {
                        return campoAtual.Valor;
                    }
                }
                if (xLocal >= 0 && xLocal < lenY)
                {
                    var campoAtual = campos.FirstOrDefault(x => x.Y == yAbaixo && x.X == xLocal);
                    if (campoAtual.ValidarCampoValor())
                    {
                        return campoAtual.Valor;
                    }
                }
                if (xPosterior >= 0 && xPosterior < lenY)
                {
                    var campoAtual = campos.FirstOrDefault(x => x.Y == yAbaixo && x.X == xPosterior);
                    if (campoAtual.ValidarCampoValor())
                    {
                        return campoAtual.Valor;
                    }
                }
            }

            return 0;
        }
    }

    public class Campo
    {
        public int Valor { get; set; } = 0;
        public int Indicador { get; set; }
        public int X { get; set; }
        public int Y { get; set; }

        public void Montar(int i, int j)
        {
            Random random = new Random();

            X = i;
            Y = j;
            Indicador = random.Next(0, 1000) > 800 ? 1 : 0;
            Valor = 0;
        }

        public bool ValidarCampoValor()
        {
            return Indicador == 1 && Valor > 0;
        }
    }
}