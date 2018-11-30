#include <stdio.h>
#include <stdlib.h>

#include "biblioteca.h"
#include "biblioteca.c"

// run with: gcc -o aai aai.c && ./aai ou gcc aai.c -o  p.exe; ./p.exe
int main(int argc, const char *argv[])
{
	Campo *campos = malloc(sizeof(Campo));
	// MontarCampos(campos); //montar com valores aleatórios
	void AtribuirPorArquivo(campos); // montar com arquivo
	ExibirCampos(campos);
	RealizarContagem(campos);
	ExibirContador();

	return 0;
}