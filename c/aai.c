#include <stdio.h>
#include <stdlib.h>

#include "biblioteca.h"

int main(int argc, const char *argv[])
{
	MontarCampos();
	ExibirCampos();
	RealizarContagem();
	ExibirContador();
	// run with: gcc -o aai aai.c && ./aai
	printf("oi gente");

	return 0;
}