#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combate.h"
#include "Structs.h"
#include "maphandling.h"
#include "interface.h"

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

Map leia_mapa(char* caminhoDoArquivo){
  Map map;
  int i, j, lixo;
  char c;
  
  FILE *file = fopen(caminhoDoArquivo, "r");
    
  map = (Map) malloc (sizeof(Map));
  /* Tem um terceiro inteiro no cabecalho do mapa
     que ninguem sabe para que serve, chamei de lixo. 
  */
  
  fscanf(file, "%d %d %d", &i, &j, &lixo);
  map->map = aloca_matriz(i, j);
  map->m = i;
  map->n = j;
  
  c = fgetc(file); // se livrando dos lixos
  c = fgetc(file);
  
  for(i = 0; i < map->m; i++){
    for(j = 0; j < map->n; j++){
      c = (int) fgetc(file);
      if(c != '|'){ 
	map->map[i][j] = c;
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

void escreva_mapa_tela(Map map, int modo){
  int i, j, OK, OK2;
  OK = OK2 = 1;
  printf(" ");
  for(i = 0; i < map->n; i++){
    printf("%d ", i + 1 );
  }
  printf("\n");

  if(modo){
    for(i = 0; i < map->m; i++){
      OK = 1;
      for(j = 0; j < map->n; j++){
	if(OK){
	  if(i <= 8)
	    printf("%d ", i + 1);
	  else
	    printf("%d ", i + 1);
	  OK = 0;
	}
	/* i linha, j coluna*/
	if(map->map[i][j] == 'C' ||
	   map->map[i][j] == 'H' ||
	   map->map[i][j] == 'D' ||
	   map->map[i][j] == 'P' ||
	   map->map[i][j] == 'S' ||
	   map->map[i][j] == ' '
	   ){
	  if(i <= 9 && j < 9)
	    printf("- ");
	  if(i > 9 && j < 9)
	    printf("- ");
	  if(i <= 9 && j >= 9)
	    printf("- ");
	  if(i > 9 && j >= 9)
	    printf("- ");
	}
	else{
	  if(i <= 9 && j < 9)
	    printf("%c ", map->map[i][j]);
	  if(i > 9 && j < 9)
	    printf("%c ", map->map[i][j]);
	  if(i <= 9 && j >= 9)
	    printf("%c ", map->map[i][j]);
	  if(i > 9 && j >= 9)
	    printf("%c ", map->map[i][j]);
	}
      }
      printf("\n");
    }
  }
  else{
    for(i = 0; i < map->m; i++){
      OK = 1;
      for(j = 0; j < map->n; j++){
	if(OK){
	  if(i <= 8)
	    printf("%d ", i + 1);
	  else
	    printf("%d ", i + 1);
	  OK = 0;
	}
	/* i linha, j coluna*/
	if(map->map[i][j] == ' '){
	  if(i <= 9 && j < 9)
	    printf(". ");
	  if(i > 9 && j < 9)
	    printf(". ");
	  if(i <= 9 && j >= 9)
	    printf(". ");
	  if(i > 9 && j >= 9)
	    printf(". ");
	}
	else{
	  if(i <= 9 && j < 9)
	    printf("%c ", map->map[i][j]);
	  if(i > 9 && j < 9)
	    printf("%c ", map->map[i][j]);
	  if(i <= 9 && j >= 9)
	    printf("%c ", map->map[i][j]);
	  if(i > 9 && j >= 9)
	    printf("%c ", map->map[i][j]);
	}
      }
      printf("\n");
    }
  }
  
}


void escreve_mapa_arquivo(Map map, int modo, char caminhoDoArquivo[], Boat barcos[], coord coordenadas[]){
  int i, j, OK;
  OK = 1;
  
  FILE *file = fopen(caminhoDoArquivo, "a+");
  
  fprintf(file , " ");
  for(i = 0; i < map->n; i++){
    fprintf(file, "%d ", i + 1 );
  }
  fprintf(file, "\n");

  if(modo){
    for(i = 0; i < map->m; i++){
      OK = 1;
      for(j = 0; j < map->n; j++){
	if(OK){
	  if(i <= 8)
	    fprintf(file, "%d ", i + 1);
	  else
	    fprintf(file, "%d ", i + 1);
	  OK = 0;
	}
	/* i linha, j coluna*/
	if(map->map[i][j] == 'C' ||
	   map->map[i][j] == 'H' ||
	   map->map[i][j] == 'D' ||
	   map->map[i][j] == 'P' ||
	   map->map[i][j] == 'S' ||
	   map->map[i][j] == ' '
	   ){
	  if(i <= 9 && j < 9)
	    fprintf(file, "- ");
	  if(i > 9 && j < 9)
	    fprintf(file, "- ");
	  if(i <= 9 && j >= 9)
	    fprintf(file, "- ");
	  if(i > 9 && j >= 9)
	    fprintf(file, "- ");
	}
	else{
	  if(i <= 9 && j < 9)
	    fprintf(file, "%c ", map->map[i][j]);
	  if(i > 9 && j < 9)
	    fprintf(file, "%c ", map->map[i][j]);
	  if(i <= 9 && j >= 9)
	    fprintf(file, "%c ", map->map[i][j]);
	  if(i > 9 && j >= 9)
	    fprintf(file, "%c ", map->map[i][j]);
	}
      }
      fprintf(file, "\n");
    }
  }
  else{
    for(i = 0; i < map->m; i++){
      OK = 1;
      for(j = 0; j < map->n; j++){
	if(OK){
	  if(i <= 8)
	    fprintf(file, "%d ", i + 1);
	  else
	    fprintf(file, "%d ", i + 1);
	  OK = 0;
	}
	/* i linha, j coluna*/
	if(map->map[i][j] == ' '){
	  if(i <= 9 && j < 9)
	    fprintf(file, ". ");
	  if(i > 9 && j < 9)
	    fprintf(file, ". ");
	  if(i <= 9 && j >= 9)
	    fprintf(file, ". ");
	  if(i > 9 && j >= 9)
	    fprintf(file, ". ");
	}
	else{
	  if(i <= 9 && j < 9)
	    fprintf(file, "%c ", map->map[i][j]);
	  if(i > 9 && j < 9)
	    fprintf(file, "%c ", map->map[i][j]);
	  if(i <= 9 && j >= 9)
	    fprintf(file, "%c ", map->map[i][j]);
	  if(i > 9 && j >= 9)
	    fprintf(file, "%c ", map->map[i][j]);
	}
      }
      fprintf(file, "\n");
    }
  }
  fclose(file);
  mensagem_turno(coordenadas, barcos, 1, caminhoDoArquivo); /*manda para o arquivo as informacoes sobre os tiros*/
}
