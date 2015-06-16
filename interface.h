#ifndef _interface_h
#define _interface_h

#include "Structs.h"

void introducao();

void mensagem_posicao();

void mensagem_posicao_invalida();

void mensagem_movimento();

void mensagem_turno(coord* coordenadas, Boat* atingidos, int modo, char caminho[]);
  
void mensagem_final(int morreu);

#endif
