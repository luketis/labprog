#ifndef _grafico_h
#define _grafico_h

#include "Structs.h"
#include "xwc.h"

WINDOW* init(char nome[], Map mapa, PIC texturas[], char caminhoTexturas[], coord* tamanhotela/*por referencia pois vou alteralo*/, int* tamanhocelula/*idem*/);

void desenha(WINDOW* win, Map mapa, PIC texturas[], char texto[], coord tamanhotela, int tamanhocelula);

void apaga(WINDOW* win, PIC texturas[]);

void desenha_fundo(WINDOW* win);

void desenha_texto(WINDOW* win, char texto[], coord xy);

void desenha_grid(WINDOW* win, Map mapa, PIC texturas[], coord tamanhotela, int tamanhocelula);

void desenha_embarcacoes(WINDOW* win, Map mapa, PIC texturas[]);

void seleciona(WINDOW* win, Map mapa, coord coordenas, PIC texturas[], int desenhado);

void desenha_celula(WINDOW* win, Map mapa, coord coordenadas, PIC texturas[], coord tamanhotela, int tamanhocelula);

void desenhar_S(WINDOW* win, coord coordenadas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]);

void desenhar_P(WINDOW* win, coord coordenadas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]);

void desenhar_C(WINDOW* win, coord coordenadas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]);

void desenhar_D(WINDOW* win, coord coordenadas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]);

void desenhar_H(WINDOW* win, coord coordenadas, Map mapa, int** desenhado, int tamanhocelula, int tipo, PIC texturas[]);
#endif
