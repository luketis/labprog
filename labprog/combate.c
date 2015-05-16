#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorteia.h"
#include "Structs.h"

/*  srand ((unsigned int) time(NULL)); */

int sorteia(int k){
  return (int)(1 + (rand()/(RAND_MAX+1.0))*k);
}

int ehembarcacao(char c){
  if(c == 'C' || c == 'D' || c == 'H' || c == 'P' || c == 'S')
    return 1;
  return 0;
}

coord* identifica_alvo_atingido(coord coordenadas[3], Map mapa){
  int i;
  coord* c = (coord*) malloc(3*sizeof(coord));
  for (i = 0; i < 3; i++) {
    c[i] = NULL;
    if(mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] == '.')   
      mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] = '=';
    
    else if(ehembarcacao(mapa->map[(coordenadas[i]).x][(coordenadas[i]).y])){
      mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] = '!';
      c[i] = coordenadas[i];
    }
    else if(mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] == 'T')
      mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] = '+';
    
    else 
      mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] = '*';
  }
  return c;
}
