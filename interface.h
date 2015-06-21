#ifndef _interface_h
#define _interface_h

#include "Structs.h"
#include "grafico.h"

char* introducao();

int get_inicio(WINDOW* w, Map mapa, PIC texturas[], coord tamanhotela, int tamanhocelula);

int get_movimento(WINDOW* w, Map mapa, PIC texturas[], coord tamanhotela, int tamanhocelula, char texto[]);

char* mensagem_posicao();

char* mensagem_posicao_invalida();

char* mensagem_movimento();

char* mensagem_movimento_invalido();

void mensagem_turno(coord* coordenadas, Boat* atingidos, int modo, char caminho[]);
  
char* mensagem_final(int morreu);

#endif
