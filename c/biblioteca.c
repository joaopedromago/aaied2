#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>

void MontarCampos(Campo *campos)
{
    int x = 0;
    int y = 0;

    Campo *campo = campos;
    while (campo->proximo != NULL)
    {
        int random = Next(0, 1000);
        campo->proximo = campos++;
        campo->X = x;
        campo->Y = y;
        campo->Indicador = random > 800 ? 1 : 0;
        campo->Valor = 0;

        x = x == lenX ? 0 : x + 1;
        y = y == lenY ? 0 : y + 1;
    }
}

void AtribuirPorArquivo(Campo *campos)
{
    FILE *fp;

    fp = fopen(file, "r");

    if (fp == NULL)
    {
        perror("Erro de leitura");
    }

    fscanf(fp, "%d %d", &lenX, &lenY);

    char readerPoint;
    int x = 0;
    int y = 0;

    while ((readerPoint = fgetc(fp)) != EOF)
    {
        if (readerPoint != ' ' && readerPoint != '\n')
        {
            Campo *atual = malloc(sizeof(Campo));

            atual->X = x;
            atual->Y = y;
            atual->Indicador = (int)readerPoint;
            atual->Valor = 0;

            if (campos != NULL)
            {
                campos->proximo = atual;
            }
            else
            {
                campos = atual;
            }
            campos++;

            y++;
            if (y == lenY)
            {
                y = 0;
                x++;
            }
            if (x == lenX)
            {
                break;
            }
        }
    }
}

void ExibirCampos(Campo *campos)
{
    Campo *campo = campos;

    while (campo != NULL)
    {
        if (campo->X == 0)
        {
            printf("\n");
        }
        printf("%d", campo->Indicador);

        campo = campo->proximo;
    }
}

void ExibirContador()
{
    printf("Total: %d", contador);
}

void RealizarContagem(Campo *campos)
{
    for (int i = 0; i < lenY; i++)
    {
        for (int j = 0; j < lenX; j++)
        {
            Campo *campo = ObterCampoPorCoordenada(campos, i, j);
            ValidarGrupo(campos, campo);
        }
    }
}

void ValidarGrupo(Campo *campos, Campo *campo)
{
    if (campo->Indicador == 1)
    {
        int auxValor = 0, auxValidador = 0;

        // validar parte acima
        auxValidador = ValidarAcima(campos, campo);
        auxValor = auxValidador == 0 ? auxValor : auxValidador;
        // validar posterior
        auxValidador = ValidarPosterior(campos, campo);
        auxValor = auxValidador == 0 ? auxValor : auxValidador;
        // validar anterior
        auxValidador = ValidarAnterior(campos, campo);
        auxValor = auxValidador == 0 ? auxValor : auxValidador;
        // validar campos abaixo
        auxValidador = ValidarAbaixo(campos, campo);
        auxValor = auxValidador == 0 ? auxValor : auxValidador;

        campo->Valor = auxValor == 0 ? ++contador : auxValor;
    }
}

int ValidarAcima(Campo *campos, Campo *campo)
{
    int yAcima = campo->Y - 1;
    int xAnterior = campo->X - 1;
    int xLocal = campo->X;
    int xPosterior = campo->X + 1;

    if (yAcima >= 0 && yAcima < lenX)
    {
        if (xAnterior >= 0 && xAnterior < lenY)
        {
            Campo *campoAtual = ObterCampoPorCoordenada(campos, yAcima, xAnterior);
            if (ValidarCampoValor(campoAtual->Indicador, campoAtual->Valor))
            {
                return campoAtual->Valor;
            }
        }
        if (xLocal >= 0 && xLocal < lenY)
        {
            Campo *campoAtual = ObterCampoPorCoordenada(campos, yAcima, xLocal);
            if (ValidarCampoValor(campoAtual->Indicador, campoAtual->Valor))
            {
                return campoAtual->Valor;
            }
        }
        if (xPosterior >= 0 && xPosterior < lenY)
        {
            Campo *campoAtual = ObterCampoPorCoordenada(campos, yAcima, xPosterior);
            if (ValidarCampoValor(campoAtual->Indicador, campoAtual->Valor))
            {
                return campoAtual->Valor;
            }
        }
    }

    return 0;
}

int ValidarPosterior(Campo *campos, Campo *campo)
{
    int yAtual = campo->Y;
    int xPosterior = campo->X + 1;

    if (yAtual >= 0 && yAtual < lenX)
    {
        if (xPosterior >= 0 && xPosterior < lenY)
        {
            Campo *campoAtual = ObterCampoPorCoordenada(campos, yAtual, xPosterior);
            if (ValidarCampoValor(campoAtual->Indicador, campoAtual->Valor))
            {
                return campoAtual->Valor;
            }
        }
    }

    return 0;
}

int ValidarAnterior(Campo *campos, Campo *campo)
{
    int yAtual = campo->Y;
    int xAnterior = campo->X - 1;

    if (yAtual >= 0 && yAtual < lenX)
    {
        if (xAnterior >= 0 && xAnterior < lenY)
        {
            Campo *campoAtual = ObterCampoPorCoordenada(campos, yAtual, xAnterior);
            if (ValidarCampoValor(campoAtual->Indicador, campoAtual->Valor))
            {
                return campoAtual->Valor;
            }
        }
    }

    return 0;
}

int ValidarAbaixo(Campo *campos, Campo *campo)
{
    int yAbaixo = campo->Y + 1;
    int xAnterior = campo->X - 1;
    int xLocal = campo->X;
    int xPosterior = campo->X + 1;

    if (yAbaixo >= 0 && yAbaixo < lenX)
    {
        if (xAnterior >= 0 && xAnterior < lenY)
        {
            Campo *campoAtual = ObterCampoPorCoordenada(campos, yAbaixo, xAnterior);
            if (ValidarCampoValor(campoAtual->Indicador, campoAtual->Valor))
            {
                return campoAtual->Valor;
            }
        }
        if (xLocal >= 0 && xLocal < lenY)
        {
            Campo *campoAtual = ObterCampoPorCoordenada(campos, yAbaixo, xLocal);
            if (ValidarCampoValor(campoAtual->Indicador, campoAtual->Valor))
            {
                return campoAtual->Valor;
            }
        }
        if (xPosterior >= 0 && xPosterior < lenY)
        {
            Campo *campoAtual = ObterCampoPorCoordenada(campos, yAbaixo, xPosterior);
            if (ValidarCampoValor(campoAtual->Indicador, campoAtual->Valor))
            {
                return campoAtual->Valor;
            }
        }
    }

    return 0;
}

Campo *ObterCampoPorCoordenada(Campo *campos, int y, int x)
{
    Campo *campo = campos;
    while (campo->proximo != NULL)
    {
        if (campo->Y == y && campo->X == x)
        {
            break;
        }
    }

    return campo;
}

int ValidarCampoValor(int Indicador, int Valor)
{
    if (Indicador == 1 && Valor > 0)
    {
        return 1;
    }

    return 0;
}