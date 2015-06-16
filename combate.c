#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Structs.h"
#include "afundador.h"
#include "combate.h"

int sorteia(int k){
  return (int)((rand() / (RAND_MAX+1.0)*k ));
}

int ehembarcacao(char c){ 
  if(c == 'C' || c == 'D' || c == 'H' || c == 'P' || c == 'S')
    return 1;
  return 0;
}

Boat* identifica_alvo_atingido(coord coordenadas[3], Map mapa, Boat barco){
  int i;

  Boat* c = (Boat*) malloc(3*sizeof(Boat));

  for(i = 0; i < 3; i++)
    c[i] = (Boat) malloc(sizeof(Boat));
  
  for (i = 0; i < 3; i++) {
    c[i]->pos.x = -1;
    c[i]->pos.y = -1;
    c[i]->alive = 1;
    c[i]->tipo = 'L';
    
    if(mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] != '*'){
      if(mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] == ' ')   
	mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] = '=';
    
      else if(ehembarcacao(mapa->map[(coordenadas[i]).x][(coordenadas[i]).y])){
	c[i]->tipo = mapa->map[(coordenadas[i]).x][(coordenadas[i]).y];
	mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] = '*';
	c[i]->pos.x = coordenadas[i].x;
	c[i]->pos.y = coordenadas[i].y;
	
      }
      else if(mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] == 'T')
	mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] = '+';
    
      else if(mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] == 'B'){ 
	barco->alive = 0;
	mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] = '!';
	}
    }
  }
    return c;
}

void afunda_embarcacao(Boat coordenadas[3], Map mapa) {
  int i;
  for(i = 0; i < 3; i++) {
    if((coordenadas[i])->pos.x != -1) {
      if(coordenadas[i]->tipo == 'D')
	afunda_destroyer(coordenadas[i]->pos, mapa);

      else if(coordenadas[i]->tipo == 'C')
	afunda_cruzador(coordenadas[i]->pos, mapa);

      else if(coordenadas[i]->tipo == 'P')
	afunda_porta_aviao(coordenadas[i]->pos, mapa);

      else if(coordenadas[i]->tipo == 'H')
	afunda_hidro_aviao(coordenadas[i]->pos, mapa);
    }
  }
		
  /*chamar a imprime_matriz_na_tela*/
}

coord* dispara_tiros(Map mapa){
  int i;
  coord *c = (coord*) malloc(3*sizeof(coord)); 
  for(i = 0; i < 3; i++){
    c[i].x = sorteia(mapa->m);
    c[i].y = sorteia(mapa->n);
  }
  return c;
}
