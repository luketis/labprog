#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorteia.h"
#include "Structs.h"

/*  srand ((unsigned int) time(NULL)); */

int sorteia(int k){
  return (int)(1 + (rand()/(RAND_MAX+1.0))*k);
}

void identifica_alvo_atingido(coord coordenadas[3], Map mapa) {
	int i;
	for (i = 0; i<3; i++) {
		if (mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] == '.') 	
			mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] = '=';

		else if (mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] == 'B')
			mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] = '!';

		else if (mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] == 'T')
			mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] = '+';
		
		else 
			mapa->map[(coordenadas[i]).x][(coordenadas[i]).y] = '*';
	}
	
}
