
int lenY = 20;
int lenX = 20;
List<Campo> campos = new List<Campo>();
int contador = 0;

struct Campo
{
    int Valor;
    int Indicador;
    int X;
    int Y;
    Campo *proximo;
};