#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combate.h"
#include "structs.h"

#define MAX 10000

char** aloca_matriz (int m, int n){
  char** matriz;
  int ind;
  matriz = malloc(m * sizeof(char*));
  
  if(matriz == NULL){
    printf("Erro ao alocar matriz.\n");
  }
  
  for (ind = 0; ind < m; ind++){
    matriz[ind] = malloc(n * sizeof(char));
    if (matriz[ind] == NULL){
      printf("Erro ao alocar matriz.\n");
    }
  }
  return matriz;
}

Boat* aloca_embarcacoes(int n){
  return (Boat*) malloc(n*sizeof(Boat));
}

void add_embarcacao(char c, Boat* embarcacoes){




}
Map leia_mapa(char caminhoDoArquivo[], Boat* embarcacoes){
  Map map;
  int i, j, lixo;
  char c, d;
    
  FILE *file = fopen(caminhoDoArquivo, "r");
  
  /* Tem um terceiro inteiro no cabecalho do mapa
     que ninguem sabe para que serve, chamei de lixo. 
  */
  
  fscanf(file, "%d %d %d", &map.m, &map.n, &lixo);
  
  map->map = aloca_matriz(map->m, map->n);
  
  c = fgetc(file); // se livrando dos lixos
  c = fgetc(file);
  
  for(i = 0; i < map->m; i++){
    for(j = 0; j < map->n; j++){
      c = (int) fgetc(file);
      if(c != '|'){ 
	map->map[i][j] = c;
	if(ehembarcacao(c))
	  add_embarcacao(c, embarcacoes);
      }
      else{
	while(c != '\n') c = fgetc(file);
	if(c == '\n'){
	  c = fgetc(file);
	  map->map[i][j] = c;
	}
      }
    }
  }

  fclose(file);
  return map;
}
