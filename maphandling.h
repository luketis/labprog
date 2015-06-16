#ifndef _maphandling_h
#define _maphandling_h

#include "Structs.h"
#include "combate.h"

Boat* aloca_embarcacoes(int n);

Map leia_mapa(char caminhoDoArquivo[]);

void escreve_mapa_tela(Map map, int modo);

void escreve_mapa_arquivo(Map map, int modo, char caminhoDoArquivo[], Boat barcos[], coord coordenadas[]);
#endif
