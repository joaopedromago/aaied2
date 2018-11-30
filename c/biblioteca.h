#ifndef BIBLIOTECA
#define BIBLIOTECA

int lenY = 20;
int lenX = 20;
int contador = 0;
char *file = "arquivo.txt";

typedef struct Campo
{
    int Valor;
    int Indicador;
    int X;
    int Y;
    struct Campo *proximo;
} Campo;

void MontarCampos(Campo *campos);
void AtribuirPorArquivo(Campo *campos, char *file);
void ExibirCampos(Campo *campos);
void ExibirContador();
void RealizarContagem(Campo *campos);
void ValidarGrupo(Campo *campos, Campo campo);
int ValidarAcima(Campo *campos, Campo campo);
int ValidarPosterior(Campo *campos, Campo campo);
int ValidarAnterior(Campo *campos, Campo campo);
int ValidarAbaixo(Campo *campos, Campo campo);
void Montar(int i, int j, int Indicador, int Valor, Campo *campos);
Campo *ObterCampoPorCoordenada(Campo *campos, int y, int x);
int ValidarCampoValor(int Indicador, int Valor);
void Adicionar(Campo *campos, Campo campo);

#endif