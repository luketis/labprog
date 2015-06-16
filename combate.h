#ifndef _combate_h
#define _combate_h

#include "Structs.h"
#include "afundador.h"

int sorteia(int k);

int ehembarcacao(char c);

Boat* identifica_alvo_atingido(coord coordenadas[3], Map mapa, Boat barco);

void afunda_embarcacao(Boat coordenadas[3], Map mapa);

coord* dispara_tiros(Map mapa);

#endif
